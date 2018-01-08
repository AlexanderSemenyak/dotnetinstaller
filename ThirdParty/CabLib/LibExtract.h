// -------------------------------------------------------
// CabLib by Elm�Soft
// www.netcult.ch/elmue
// -------------------------------------------------------


#pragma once

#include <gcroot.h>
#include "Cabinet/Extract.hpp"
#include "Cabinet/ExtractMemory.hpp"
#include "Cabinet/ExtractResource.hpp"
#include "Cabinet/ExtractStream.hpp"
#include "Cabinet/ExtractUrl.hpp"

using namespace System;
using namespace System::IO;
using namespace System::Threading;
using namespace System::Collections;
using namespace System::Runtime::InteropServices;

namespace CabLib
{
    public ref class Extract
    {
    public:
        ref struct kCabinetInfo
        {
            String^   s_NextCabinet;  // Name of the next cabinet excluding path info
            String^   s_NextDisk;     // Name of the next disk
            String^   s_Path;         // Path to the cabinet
            UInt16  u16_SetID;        // The set ID of this cabinet
            UInt16  u16_Cabinet;      // The cabinet number within the cabinet set (starting at 0)

            ~kCabinetInfo() {}     // Destructor is required!
        };

        ref struct kCabinetFileInfo
        {
            String^    s_File;        // Only the filename of the file
            String^    s_SubFolder;   // The subfolder in the CAB file
            String^    s_RelPath;     // relative path = s_SubFolder + s_File
            String^    s_Path;        // The full path to the file on disk
            String^    s_FullPath;    // The full path to the file plus the filename
            Int32    s32_Size;        // Uncompressed file size
            DateTime   k_Time;        // Time and date of the file
            UInt16   u16_Attribs;     // Attributes of the file

            ~kCabinetFileInfo() {} // Destructor is required!
        };

        ref struct kProgressInfo
        {
            String^    s_RelPath;  // The relative path in the CAB file
            String^    s_FullPath; // The full path to the file on disk
            UInt32   u32_TotSize;  // Uncompressed file size
            UInt32   u32_Written;  // Bytes written to disk
            Single    fl_Percent;  // Percent written

            ~kProgressInfo() {} // Destructor is required!
        };

        ref struct kHeaderInfo // this data is read from the CAB header
        {
            UInt32   u32_FileSize;  // Total length of cabinet file
            UInt16   u16_Folders;   // Count of folders in cabinet
            UInt16   u16_Files;     // Count of files in cabinet
            UInt16   u16_SetID;     // Cabinet set ID
            UInt16   u16_CabIndex;  // zero based Cabinet number in multi file set (splitted archive)
            bool     b_HasReserve;  // true => has additional data in the CAB header
            bool     b_HasPrevious; // true => Cabinet file has predecessor file in a splitted archive
            bool     b_HasNext;     // true => Cabinet file has succesor    file in a splitted archive
        };

        Extract();
        ~Extract();
        void CleanUp();
        // for all types of extraction:
        void AbortOperation     ();
        void SetDecryptionKey   (String^ s_Password);
        void SetDecryptionKey   (array<Byte>^ u8_Key);
        void SetCodepage        (UInt32 u32_Codepage);
        void SetSingleFile      (String^ s_File);
        void SetProgressInterval(int s32_CallbackInterval);
        // Extraction functions:
        void ExtractFile        (String^ s_CabFile, String^ s_Folder);
        void ExtractResource    (String^ s_Module,  Object^ o_RscName, Object^ o_RscType, String^ s_Folder);
        void ExtractStream      (Stream^ i_Stream,  String^ s_Folder);
        // File Information
        bool IsFileCabinet      (String^ s_CabFile, [Out] kHeaderInfo^% pk_HeaderInfo);
        // Internet Extraction:
        void SetPassiveFtpMode  (bool b_Passive);
        void SetProxy           (String^ s_ProxyString);
        void SetHttpHeaders     (String^ s_Headers);
        void InternetGetProgress([Out] Int32^% s32_Total, [Out] Int32^% s32_Read);
        void ExtractUrl         (String^ s_Url, Int32 s32_BlockSize, String^ s_LocalPath, String^ s_Folder);
        void ExtractMoreUrl     (String^ s_Folder);
        
        static bool ResolveShortcut(String^ s_File, [Out] String^% s_Url, [Out] String^% s_Lnk);

        delegate bool delBeforeCopyFile(kCabinetFileInfo^ k_Info);
        delegate void delAfterCopyFile(String^ s_File, array<Byte>^ u8_ExtractMem);
        delegate void delProgressInfo(kProgressInfo^ k_Info);
        delegate void delCabinetInfo(kCabinetInfo^ k_Info);
        delegate void delNextCabinet(kCabinetInfo^ k_Info, Int32 s32_FdiError);

        event delBeforeCopyFile^ evBeforeCopyFile;
        event delAfterCopyFile^  evAfterCopyFile;
        event delProgressInfo^   evProgressInfo;
        event delCabinetInfo^    evCabinetInfo;
        event delNextCabinet^    evNextCabinet;

    private:
        void Reset();

        Cabinet::CExtract*  mi_Extract;
        String^             ms_SingleFile;
        int               ms32_ProgressInterval;
        UInt32            mu32_Codepage;
        bool                mb_Internet;
        bool                mb_Passive;
        bool                mb_ExtractMem;
        String^             ms_Proxy;
        String^             ms_Headers;
        array<Byte>^       mu8_Key;

        // These functions are called only from cCallbackBridge. They should not be visible from outside the Assembly.
        // cCallbackBridge cannot fire events of another class -> Error C3918
    internal:
        bool FireBeforeCopyFile(kCabinetFileInfo^ k_Info)
        {
            // The check for event == null is not required in CLI
            return evBeforeCopyFile(k_Info);
        }
        void FireAfterCopyFile(String^ s_File, [Out] array<Byte>^% u8_ExtractMem)
        {
            // The check for event == null is not required in CLI
            evAfterCopyFile(s_File, u8_ExtractMem);
        }
        void FireProgressInfo(kProgressInfo^ k_Info)
        {
            // The check for event == null is not required in CLI
            evProgressInfo(k_Info);
        }
        void FireCabinetInfo(kCabinetInfo^ k_Info)
        {
            // The check for event == null is not required in CLI
            evCabinetInfo(k_Info);
        }
        void FireNextCabinet(kCabinetInfo^ k_Info, Int32 s32_FdiError)
        {
            // The check for event == null is not required in CLI
            evNextCabinet(k_Info, s32_FdiError);
        }
    };
};

// A bridge class to pass native callbacks to managed code.
// This class MUST be exactly like this!!!! Microsoft did not provide an easier way!
// It is impossible to pass a managed function pointer to native C++ code.
// This could be done using Marshal::StructureToPtr() but this will function only for the first time.
// When the framework moves the delegate in memory to another location the callbacks will fail.
// The !!ONLY!! reliable way to pass delegates to native code is via Pinning using a GCHandle.
// But this is incompatible with native code. 
// Native code cannot call a pinned pointer as if it was a real function pointer.
namespace CabLib
{
    class cExtractBridge
    {
    private:
        Cabinet::CExtract::kCallbacks mk_Callbacks;
        gcroot<Extract^>    mi_Instance;
        gcroot<String^>     ms_SingleFile;
        gcroot<Stream^>     mi_Stream;

    public:

        // All these members must be copied HERE because the stupid compiler does not allow to access
        // members of the owning Extract class!
        // The events can not be fired from within the callbacks of the bridge class
        cExtractBridge(gcroot<Extract^> i_Instance,
                       gcroot<String^>  s_SingleFile,
                       gcroot<Stream^>  i_Stream,
                       int              s32_ProgressInterval)
        {
            mi_Instance   = i_Instance;
            ms_SingleFile = s_SingleFile;
            mi_Stream     = i_Stream;

            mk_Callbacks.f_OnBeforeCopyFile   = OnBeforeCopyFile;
            mk_Callbacks.f_OnAfterCopyFile    = OnAfterCopyFile;
            mk_Callbacks.f_OnProgressInfo     = OnProgressInfo;
            mk_Callbacks.f_OnCabinetInfo      = OnCabinetInfo;
            mk_Callbacks.f_OnNextCabinet      = OnNextCabinet;
            mk_Callbacks.f_StreamGetLen       = OnStreamGetLen;
            mk_Callbacks.f_StreamRead         = OnStreamRead;
            mk_Callbacks.s32_ProgressInterval = s32_ProgressInterval;
        }

        Cabinet::CExtract::kCallbacks* GetCallbacks()
        {
            return &mk_Callbacks;
        }

        // The folling callbacks are called directly from native C++ code:
        static BOOL OnBeforeCopyFile(Cabinet::CExtract::kCabinetFileInfo* pk_Info, void* p_Param);
        static void OnAfterCopyFile(WCHAR* u16_File, Cabinet::CMemory* pi_ExtractMem, void* p_Param);
        static void OnProgressInfo(Cabinet::CExtract::kProgressInfo* pk_Info, void* p_Param);
        static void OnCabinetInfo(Cabinet::CExtract::kCabinetInfo* pk_Info, void* p_Param);
        static void OnNextCabinet(Cabinet::CExtract::kCabinetInfo* pk_Info, int s32_FdiError, void* p_Param);
        static int  OnStreamGetLen(void* p_Param);
        static int  OnStreamRead  (void* p_Buffer, int Pos, UINT u32_Count, void* p_Param);
    };
};


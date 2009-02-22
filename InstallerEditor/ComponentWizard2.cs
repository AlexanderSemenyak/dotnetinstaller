using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;

namespace InstallerEditor
{
	/// <summary>
	/// Summary description for ComponentWizard.
	/// </summary>
	public class ComponentWizard2 : System.Windows.Forms.Form
	{
		private System.Windows.Forms.CheckedListBox chkListComponents;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.GroupBox groupBoxDownloaded;
		private System.Windows.Forms.TextBox txtSupportFilesWebSite;
		private System.Windows.Forms.TextBox txtSupportFilesFileSystem;
		private System.Windows.Forms.Button btBrowseSupportFilesFileSystem;
		private System.Windows.Forms.Button btCancel;
		private System.Windows.Forms.Button btOK;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.GroupBox groupBoxSupportFilesFileSystem;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public ComponentWizard2()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();
		}

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		protected override void Dispose( bool disposing )
		{
			if( disposing )
			{
				if(components != null)
				{
					components.Dispose();
				}
			}
			base.Dispose( disposing );
		}

		#region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.chkListComponents = new System.Windows.Forms.CheckedListBox();
			this.label1 = new System.Windows.Forms.Label();
			this.groupBoxDownloaded = new System.Windows.Forms.GroupBox();
			this.txtSupportFilesWebSite = new System.Windows.Forms.TextBox();
			this.groupBoxSupportFilesFileSystem = new System.Windows.Forms.GroupBox();
			this.txtSupportFilesFileSystem = new System.Windows.Forms.TextBox();
			this.btBrowseSupportFilesFileSystem = new System.Windows.Forms.Button();
			this.btCancel = new System.Windows.Forms.Button();
			this.btOK = new System.Windows.Forms.Button();
			this.label2 = new System.Windows.Forms.Label();
			this.groupBoxDownloaded.SuspendLayout();
			this.groupBoxSupportFilesFileSystem.SuspendLayout();
			this.SuspendLayout();
			// 
			// chkListComponents
			// 
			this.chkListComponents.CheckOnClick = true;
			this.chkListComponents.Location = new System.Drawing.Point(8, 24);
			this.chkListComponents.Name = "chkListComponents";
			this.chkListComponents.Size = new System.Drawing.Size(460, 109);
			this.chkListComponents.TabIndex = 0;
			// 
			// label1
			// 
			this.label1.Location = new System.Drawing.Point(8, 4);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(312, 20);
			this.label1.TabIndex = 1;
			this.label1.Text = "Components to install";
			// 
			// groupBoxDownloaded
			// 
			this.groupBoxDownloaded.Controls.Add(this.txtSupportFilesWebSite);
			this.groupBoxDownloaded.Location = new System.Drawing.Point(8, 148);
			this.groupBoxDownloaded.Name = "groupBoxDownloaded";
			this.groupBoxDownloaded.Size = new System.Drawing.Size(464, 44);
			this.groupBoxDownloaded.TabIndex = 3;
			this.groupBoxDownloaded.TabStop = false;
			this.groupBoxDownloaded.Text = "Downloaded from Internet (WEBSETUP Components)";
			// 
			// txtSupportFilesWebSite
			// 
			this.txtSupportFilesWebSite.Location = new System.Drawing.Point(4, 16);
			this.txtSupportFilesWebSite.Name = "txtSupportFilesWebSite";
			this.txtSupportFilesWebSite.Size = new System.Drawing.Size(424, 20);
			this.txtSupportFilesWebSite.TabIndex = 1;
			this.txtSupportFilesWebSite.Text = "http://www.myWebSite.com/MyApp/SupportFiles";
			// 
			// groupBoxSupportFilesFileSystem
			// 
			this.groupBoxSupportFilesFileSystem.Controls.Add(this.txtSupportFilesFileSystem);
			this.groupBoxSupportFilesFileSystem.Controls.Add(this.btBrowseSupportFilesFileSystem);
			this.groupBoxSupportFilesFileSystem.Location = new System.Drawing.Point(8, 196);
			this.groupBoxSupportFilesFileSystem.Name = "groupBoxSupportFilesFileSystem";
			this.groupBoxSupportFilesFileSystem.Size = new System.Drawing.Size(464, 44);
			this.groupBoxSupportFilesFileSystem.TabIndex = 4;
			this.groupBoxSupportFilesFileSystem.TabStop = false;
			this.groupBoxSupportFilesFileSystem.Text = "Distribuited with dotNetInstaller (STANDARD Components)";
			// 
			// txtSupportFilesFileSystem
			// 
			this.txtSupportFilesFileSystem.Location = new System.Drawing.Point(4, 16);
			this.txtSupportFilesFileSystem.Name = "txtSupportFilesFileSystem";
			this.txtSupportFilesFileSystem.Size = new System.Drawing.Size(424, 20);
			this.txtSupportFilesFileSystem.TabIndex = 1;
			this.txtSupportFilesFileSystem.Text = "#APPPATH\\SupportFiles";
			// 
			// btBrowseSupportFilesFileSystem
			// 
			this.btBrowseSupportFilesFileSystem.Location = new System.Drawing.Point(432, 16);
			this.btBrowseSupportFilesFileSystem.Name = "btBrowseSupportFilesFileSystem";
			this.btBrowseSupportFilesFileSystem.Size = new System.Drawing.Size(28, 20);
			this.btBrowseSupportFilesFileSystem.TabIndex = 0;
			this.btBrowseSupportFilesFileSystem.Text = "...";
			// 
			// btCancel
			// 
			this.btCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this.btCancel.Location = new System.Drawing.Point(396, 348);
			this.btCancel.Name = "btCancel";
			this.btCancel.TabIndex = 5;
			this.btCancel.Text = "Cancel";
			// 
			// btOK
			// 
			this.btOK.Location = new System.Drawing.Point(308, 348);
			this.btOK.Name = "btOK";
			this.btOK.TabIndex = 6;
			this.btOK.Text = "OK";
			this.btOK.Click += new System.EventHandler(this.btOK_Click);
			// 
			// label2
			// 
			this.label2.BackColor = System.Drawing.SystemColors.Info;
			this.label2.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
			this.label2.ForeColor = System.Drawing.SystemColors.InfoText;
			this.label2.Location = new System.Drawing.Point(4, 244);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(472, 100);
			this.label2.TabIndex = 0;
			this.label2.Text = @"The wizard automatically add the relative path of each component based on the standard structure of the SupportFiles directory that you can download from: www.devage.com . Here you must only write the root path of the SupportFiles directory.  Remember that you must insert the components in the correct order and you must select the language based on the LCID used in the parent configuration node. If you select ""Download from the Internet"" you must also select the components with WebSetup name otherwise you must select the Standard components.";
			// 
			// ComponentWizard2
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(478, 377);
			this.Controls.Add(this.btOK);
			this.Controls.Add(this.btCancel);
			this.Controls.Add(this.groupBoxSupportFilesFileSystem);
			this.Controls.Add(this.groupBoxDownloaded);
			this.Controls.Add(this.label1);
			this.Controls.Add(this.chkListComponents);
			this.Controls.Add(this.label2);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "ComponentWizard2";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
			this.Text = "ComponentWizard 2";
			this.Load += new System.EventHandler(this.ComponentWizard_Load);
			this.groupBoxDownloaded.ResumeLayout(false);
			this.groupBoxSupportFilesFileSystem.ResumeLayout(false);
			this.ResumeLayout(false);

		}
		#endregion

		private void ComponentWizard_Load(object sender, System.EventArgs e)
		{
			//supported component
			chkListComponents.Items.Clear();

			System.Xml.XmlDocument doc = new System.Xml.XmlDocument();
			System.Reflection.Assembly assembly = System.Reflection.Assembly.GetExecutingAssembly();
			doc.Load(assembly.GetManifestResourceStream("InstallerEditor.templates.components.xml"));

			System.Xml.XmlNodeList list = doc.SelectNodes("//components/component");
			foreach (System.Xml.XmlElement element in list)
			{
				chkListComponents.Items.Add(new ComponentFromXML(element.OuterXml));
			}
		}

		private ComponentCollection m_SelectedComponents = new ComponentCollection();

		private void btOK_Click(object sender, System.EventArgs e)
		{
			try
			{
				foreach (WizardComponent w in chkListComponents.CheckedItems)
				{
					m_SelectedComponents.AddRange(w.CreateComponent(txtSupportFilesWebSite.Text, txtSupportFilesFileSystem.Text));
				}
				
				DialogResult = DialogResult.OK;
			}
			catch(Exception err)
			{
				AppUtility.ShowError(this, err);
			}
		}

		public ComponentCollection SelectedComponents
		{
			get{return m_SelectedComponents;}
		}

		private abstract class WizardComponent
		{
			private string m_Description;
			public string Description
			{
				get{return m_Description;}
				set{m_Description = value;}
			}
			public WizardComponent()
			{
			}

			public override string ToString()
			{
				return m_Description;
			}

			public abstract Component[] CreateComponent(string p_WebSetupPath, string StandardPath);
		}

		private class ComponentFromXML : WizardComponent
		{
			private string m_RawXml;

			public ComponentFromXML(string xmlComponent)
			{
				m_RawXml = xmlComponent;

				System.Xml.XmlDocument doc = new System.Xml.XmlDocument();
				doc.LoadXml(xmlComponent);
				Component c = Component.CreateComponentFromXml(doc.DocumentElement);

				Description = c.note;
			}

			public override Component[] CreateComponent(string p_WebSetupPath, string StandardPath)
			{
				m_RawXml = m_RawXml.Replace("#APPPATH\\SupportFiles", StandardPath);
				m_RawXml = m_RawXml.Replace("http://www.YOURWEBSITE.com/MyApp/SupportFiles", p_WebSetupPath);

				System.Xml.XmlDocument doc = new System.Xml.XmlDocument();
				doc.LoadXml(m_RawXml);
				Component c = Component.CreateComponentFromXml(doc.DocumentElement);

				return new Component[]{c};
			}
		}
	}

}
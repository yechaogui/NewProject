namespace 注册表修改工具
{
    partial class 注册表修改工具
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.OpenReg_bt = new System.Windows.Forms.Button();
            this.RegPath_tB = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // OpenReg_bt
            // 
            this.OpenReg_bt.Location = new System.Drawing.Point(12, 12);
            this.OpenReg_bt.Name = "OpenReg_bt";
            this.OpenReg_bt.Size = new System.Drawing.Size(75, 23);
            this.OpenReg_bt.TabIndex = 0;
            this.OpenReg_bt.Text = "打开注册表";
            this.OpenReg_bt.UseVisualStyleBackColor = true;
            this.OpenReg_bt.Click += new System.EventHandler(this.OpenReg_bt_Click);
            // 
            // RegPath_tB
            // 
            this.RegPath_tB.Location = new System.Drawing.Point(93, 14);
            this.RegPath_tB.Name = "RegPath_tB";
            this.RegPath_tB.Size = new System.Drawing.Size(479, 21);
            this.RegPath_tB.TabIndex = 1;
            this.RegPath_tB.Text = "C:\\Windows\\regedit.exe";
            // 
            // 注册表修改工具
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(584, 450);
            this.Controls.Add(this.RegPath_tB);
            this.Controls.Add(this.OpenReg_bt);
            this.Name = "注册表修改工具";
            this.Text = "注册表修改工具";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button OpenReg_bt;
        private System.Windows.Forms.TextBox RegPath_tB;
    }
}


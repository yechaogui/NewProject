namespace Gui工具箱
{
    partial class Form1
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
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.文件夹同步助手ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.文件夹同步助手ToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripSeparator();
            this.功能2ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.常用软件设置ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.清除修复XToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.退出QToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.文件夹同步助手ToolStripMenuItem,
            this.常用软件设置ToolStripMenuItem,
            this.清除修复XToolStripMenuItem,
            this.退出QToolStripMenuItem1});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(584, 25);
            this.menuStrip1.TabIndex = 12;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // 文件夹同步助手ToolStripMenuItem
            // 
            this.文件夹同步助手ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.文件夹同步助手ToolStripMenuItem1,
            this.toolStripMenuItem1,
            this.功能2ToolStripMenuItem});
            this.文件夹同步助手ToolStripMenuItem.Name = "文件夹同步助手ToolStripMenuItem";
            this.文件夹同步助手ToolStripMenuItem.Size = new System.Drawing.Size(88, 21);
            this.文件夹同步助手ToolStripMenuItem.Text = "常用工具(&M)";
            // 
            // 文件夹同步助手ToolStripMenuItem1
            // 
            this.文件夹同步助手ToolStripMenuItem1.Name = "文件夹同步助手ToolStripMenuItem1";
            this.文件夹同步助手ToolStripMenuItem1.Size = new System.Drawing.Size(180, 22);
            this.文件夹同步助手ToolStripMenuItem1.Text = "文件夹同步助手";
            this.文件夹同步助手ToolStripMenuItem1.Click += new System.EventHandler(this.文件夹同步助手ToolStripMenuItem1_Click);
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(157, 6);
            // 
            // 功能2ToolStripMenuItem
            // 
            this.功能2ToolStripMenuItem.Name = "功能2ToolStripMenuItem";
            this.功能2ToolStripMenuItem.Size = new System.Drawing.Size(160, 22);
            this.功能2ToolStripMenuItem.Text = "功能2";
            // 
            // 常用软件设置ToolStripMenuItem
            // 
            this.常用软件设置ToolStripMenuItem.Name = "常用软件设置ToolStripMenuItem";
            this.常用软件设置ToolStripMenuItem.Size = new System.Drawing.Size(109, 21);
            this.常用软件设置ToolStripMenuItem.Text = "常用软件设置(&G)";
            // 
            // 清除修复XToolStripMenuItem
            // 
            this.清除修复XToolStripMenuItem.Name = "清除修复XToolStripMenuItem";
            this.清除修复XToolStripMenuItem.Size = new System.Drawing.Size(84, 21);
            this.清除修复XToolStripMenuItem.Text = "清除修复(&X)";
            // 
            // 退出QToolStripMenuItem1
            // 
            this.退出QToolStripMenuItem1.Name = "退出QToolStripMenuItem1";
            this.退出QToolStripMenuItem1.ShortcutKeys = ((System.Windows.Forms.Keys)(((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Shift) 
            | System.Windows.Forms.Keys.Q)));
            this.退出QToolStripMenuItem1.Size = new System.Drawing.Size(62, 21);
            this.退出QToolStripMenuItem1.Text = "退出(&Q)";
            this.退出QToolStripMenuItem1.Click += new System.EventHandler(this.退出QToolStripMenuItem1_Click);
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(12, 28);
            this.textBox1.Multiline = true;
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(560, 371);
            this.textBox1.TabIndex = 13;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(584, 411);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.menuStrip1);
            this.MaximumSize = new System.Drawing.Size(600, 450);
            this.MinimumSize = new System.Drawing.Size(600, 450);
            this.Name = "Form1";
            this.Text = "Gui工具箱";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem 文件夹同步助手ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 文件夹同步助手ToolStripMenuItem1;
        private System.Windows.Forms.ToolStripSeparator toolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem 功能2ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 常用软件设置ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 清除修复XToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 退出QToolStripMenuItem1;
        private System.Windows.Forms.TextBox textBox1;
    }
}


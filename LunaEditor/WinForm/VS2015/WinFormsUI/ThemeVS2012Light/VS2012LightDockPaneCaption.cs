blank" class="link">Parallax Bumpmapping Whitepaper</a></li>
				<li><a href="../Whitepapers/Post Processing Effects.Whitepaper.pdf" target="_blank" class="link">Post Processing Effects Whitepaper</a></li>
				<li><a href="../Whitepapers/Shader Based Water Effects.Whitepaper.pdf" target="_blank" class="link">Shader Based Water Effects Whitepaper</a></li>
				<li><a href="../Whitepapers/UI Example.Whitepaper.pdf" target="_blank" class="link">UI Example Whitepaper</a></li>
			</ul>
		</div>
	</div>
	<br>
    <div id="FooterMainContainer">
		<div id="FooterContainer">
			<div class="footerlogo">
				<a href="http://www.imgtec.com" target="_blank"><img src="./images/img-footer-logo-grey.png" width="100%" height="100%" /></a>
			</div>
			<div class="copyright">&copy; Imagination Technologies Limited<br> All rights reserved</div>
		</div>
	</div>
</body>

</html>                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          nAutoHide);
                }

                return m_buttonAutoHide;
            }
        }

        private static Bitmap _imageButtonOptions;
        private static Bitmap ImageButtonOptions
        {
            get
            {
                if (_imageButtonOptions == null)
                    _imageButtonOptions = Resources.DockPane_Option;

                return _imageButtonOptions;
            }
        }

        private InertButton m_buttonOptions;
        private InertButton ButtonOptions
        {
            get
            {
                if (m_buttonOptions == null)
                {
                    m_buttonOptions = new InertButton(this, ImageButtonOptions, ImageButtonOptions);
                    m_toolTip.SetToolTip(m_buttonOptions, ToolTipOptions);
                    m_buttonOptions.Click += new EventHandler(Options_Click);
                    Controls.Add(m_buttonOptions);
                }
                return m_buttonOptions;
            }
        }

        private IContainer m_components;
        private IContainer Components
        {
            get { return m_components; }
        }

        private ToolTip m_toolTip;

        public VS2012LightDockPaneCaption(DockPane pane) : base(pane)
        {
            SuspendLayout();

            m_components = new Container();
            m_toolTip = new ToolTip(Components);

            ResumeLayout();
        }

        protected override void Dispose(bool disposing)
        {
            if (disposing)
                Components.Dispose();
            base.Dispose(disposing);
        }

        private static int TextGapTop
        {
            get	{	return _TextGapTop;	}
        }

        public Font TextFont
        {
            get { return DockPane.DockPanel.Skin.DockPaneStripSkin.TextFont; }
        }

        private static int TextGapBottom
        {
            get	{	return _TextGapBottom;	}
        }

        private static int TextGapLeft
        {
            get	{	return _TextGapLeft;	}
        }

        private static int TextGapRight
        {
            get	{	return _TextGapRight;	}
        }

        private static int ButtonGapTop
        {
            get	{	return _ButtonGapTop;	}
        }

        private static int ButtonGapBottom
        {
            get	{	return _ButtonGapBottom;	}
        }

        private static int ButtonGapLeft
        {
            get	{	return _ButtonGapLeft;	}
        }

        private static int ButtonGapRight
        {
            get	{	return _ButtonGapRight;	}
        }

        private static int ButtonGapBetween
        {
            get	{	return _ButtonGapBetween;	}
        }

        private static string _toolTipClose;
        private static string ToolTipClose
        {
            get
            {	
                if (_toolTipClose == null)
                    _toolTipClose = Strings.DockPaneCaption_ToolTipClose;
                return _toolTipClose;
            }
        }

        private static string _toolTipOptions;
        private static string ToolTipOptions
        {
            get
            {
                if (_toolTipOptions == null)
                    _toolTipOptions = Strings.DockPaneCaption_ToolTipOptions;

                return _toolTipOptions;
            }
        }

        private static string _toolTipAutoHide;
        private static string ToolTipAutoHide
        {
            get
            {	
                if (_toolTipAutoHide == null)
                    _toolTipAutoHide = Strings.DockPaneCaption_ToolTipAutoHide;
                return _toolTipAutoHide;
            }
        }

        private static Blend _activeBackColorGradientBlend;
        private static Blend ActiveBackColorGradientBlend
        {
            get
            {
                if (_activeBackColorGradientBlend == null)
                {
                    Blend blend = new Blend(2);

                    blend.Factors = new float[]{0.5F, 1.0F};
                    blend.Positions = new float[]{0.0F, 1.0F};
                    _activeBackColorGradientBlend = blend;
                }

                return _activeBackColorGradientBlend;
            }
        }

        private Color TextColor
        {
            get
            {
                if (DockPane.IsActivated)
                    return DockPane.DockPanel.Skin.DockPaneStripSkin.ToolWindowGradient.ActiveCaptionGradient.TextColor;
                else
                    return DockPane.DockPanel.Skin.DockPaneStripSkin.ToolWindowGradient.InactiveCaptionGradient.TextColor;
            }
        }

        private static TextFormatFlags _textFormat =
            TextFormatFlags.SingleLine |
            TextFormatFlags.EndEllipsis |
            TextFormatFlags.VerticalCenter;
        private TextFormatFlags TextFormat
        {
            get
            {
                if (RightToLeft == RightToLeft.No)
                    return _textFormat;
                else
                    return _textFormat | TextFormatFlags.RightToLeft | TextFormatFlags.Right;
            }
        }

        protected override int MeasureHeight()
        {
            int height = TextFont.Height + TextGapTop + TextGapBottom;

            if (height < ButtonClose.Image.Height + ButtonGapTop + ButtonGapBottom)
                height = ButtonClose.Image.Height + ButtonGapTop + ButtonGapBottom;

            return height;
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint (e);
            DrawCaption(e.Graphics);
        }

        private void DrawCaption(Graphics g)
        {
            if (ClientRectangle.Width == 0 || ClientRectangle.Height == 0)
                return;

            Rectangle rect = ClientRectangle;
            Color captionColor;

            if (DockPane.IsActivated)
                captionColor = DockPane.DockPanel.Skin.DockPaneStripSkin.ToolWindowGradient.ActiveCaptionGradient.StartColor;
            else
                captionColor = DockPane.DockPanel.Skin.DockPaneStripSkin.ToolWindowGradient.InactiveCaptionGradient.StartColor;

            SolidBrush captionBrush = new SolidBrush(captionColor);
            g.FillRectangle(captionBrush, rect);

            Rectangle rectCaption = rect;

            Rectangle rectCaptionText = rectCaption;
            rectCaptionText.X += TextGapLeft;
            rectCaptionText.Width -= TextGapLeft + TextGapRight;
            rectCaptionText.Width -= ButtonGapLeft + ButtonClose.Width + ButtonGapRight;
            if (ShouldShowAutoHideButton)
                rectCaptionText.Width -= ButtonAutoHide.Width + ButtonGapBetween;
            if (HasTabPageContextMenu)
                rectCaptionText.Width -= ButtonOptions.Width + ButtonGapBetween;
            rectCaptionText.Y += TextGapTop;
            rectCaptionText.Height -= TextGapTop + TextGapBottom;

            Color colorText;
            if (DockPane.IsActivated)
                colorText = DockPane.DockPanel.Skin.DockPaneStripSkin.ToolWindowGradient.ActiveCaptionGradient.TextColor;
            else
                colorText = DockPane.DockPanel.Skin.DockPaneStripSkin.ToolWindowGradient.InactiveCaptionGradient.TextColor;

            TextRenderer.DrawText(g, DockPane.CaptionText, TextFont, DrawHelper.RtlTransform(this, rectCaptionText), colorText, TextFormat);

            Rectangle rectDotsStrip = rectCaptionText;
            int textLength = (int)g.MeasureString(DockPane.CaptionText, TextFont).Width + TextGapLeft;
            rectDotsStrip.X += textLength;
            rectDotsStrip.Width -= textLength;
            rectDotsStrip.Height = ClientRectangle.Height;

            Color dotsColor;
            if (DockPane.IsActivated)
                dotsColor = DockPane.DockPanel.Skin.DockPaneStripSkin.ToolWindowGradient.ActiveCaptionGradient.EndColor;
            else
                dotsColor = DockPane.DockPanel.Skin.DockPaneStripSkin.ToolWindowGradient.InactiveCaptionGradient.EndColor;

            DrawDotsStrip(g, rectDotsStrip, dotsColor);
        }

        protected void DrawDotsStrip(Graphics g, Rectangle rectStrip, Color colorDots)
        {
            if (rectStrip.Wi or -fft=N</td><td>Force PVRShellGetTime to report fixed frame time.</td>
				</tr>
				<tr>
					<td>-fps</td><td>Output frames per second.</td>
				</tr>
				<tr>
					<td>-fullscreen=[1,0]</td><td>Runs in full-screen mode (1) or windowed (0).</td>
				</tr>
				<tr>
					<td>-height=N</td><td>Sets the viewport height to N.</td>
				</tr>
				<tr>
					<td>-info</td><td>Output setup information to the debug output.</td>
				</tr>
				<tr>
					<td>-posx=N</td><td>Sets the x coordinate of the viewport.</td>
				</tr>
				<tr>
					<td>-posy=N</td><td>Sets the y coordinate of the viewport.</td>
				</tr>
				<tr>
					<td>-powersaving=[1,0] or -ps=[1,0]</td><td>Where available enable/disable power saving.</td>
				</tr>
				<tr>
					<td>-priority=N</td><td>Sets the priority of the EGL context.</td>
				</tr>
				<tr>
					<td>-quitafterframe=N or -qaf=N</td><td>Specify the frame after which to quit.</td>
				</tr>
				<tr>
					<td>-quitaftertime=N or -qat=N</td><td>Specify the time after which to quit.</td>
				</tr>
				<tr>
					<td>-rotatekeys=N</td><td>Sets the orientation of the keyboard input. N can be 0-3, where 0 is no rotation.</td>
				</tr>
				<tr>
					<td>-screenshotscale=N</td><td>Allows to scale up screenshots to a bigger size (pixel replication).</td>
				</tr>
				<tr>
					<td>-sw</td><td>Software render.</td>
				</tr>
				<tr>
					<td>-version</td><td>Output the SDK version to the debug output.</td>
				</tr>
				<tr>
					<td>-vsync=N</td><td>Where available modify the app's vsync parameters.</td>
				</tr>
				<tr>
					<td>-width=N</td><td>Sets the viewport width to N.</td>
				</tr>
			</table>
			<p>PVRShell also provides limited keyboard input which may vary depending on your actual platform. If your platform has full keyboard support, the <span class="code">Q</span> key will quit the application and the cursor keys will allow looping through the application options.</p>
			<p>The PVRShell source can be found in the <a href="../../Shell/">Shell</a> folder in the SDK package. Further documentation is available at <a href="../../Shell/Documentation/Index.html">Shell/Documentation</a>.</p>
		</div>
		<div id="PVRTools">
			<h2>PVRTools</h2>
			<p>The PVRTools library consists of various modules designed to facilitate common tasks associated with hardware accelerated graphics rendering. This includes:</p>
			<ul>
				<li><p><strong>Vector, matrix and quaternion mathematics:</strong> Helpers to calculate and operate transformation matrices and other associated mathematical operations.</p></li>
				<li><p><strong>OpenGL ES extension handling:</strong> This helps to load and use OpenGL ES extension functions and capabilities.</p></li>
				<li><p><strong>3D font drawing:</strong> A very flexible engine to handle font maps.</p></li>
				<li><p><strong>POD loader:</strong> Helpers to load and access the model data included in PowerVR Object Data (POD) files.</p></li>
				<li><p><strong>PVR loader:</strong> Helpers to upload and manage textures exported to the PVR texture container format.</p></li>
				<li><p><strong>PFX loader:</strong> Helpers to load and access PowerVR Effects (PFX) files, which contain vertex and fragment shaders.</p></li>
			</ul>
			<p>The Tools library is used extensively throughout the PowerVR SDK. The PVRTools source can be found in the <a href="../../Tools/">Tools</a> folder in the SDK package. Further documentation is available at <a href="../../Tools/Documentation/Index.html">Tools/Documentation</a>.</p>
		</div>
	</div>
	<br>
    <div id="FooterMainContainer">
		<div id="FooterContainer">
			<div class="footerlogo">
				<a href="http://www.imgtec.com" target="_blank"><img src="./images/img-footer-logo-grey.png" width="100%" height="100%" /></a>
			</div>
			<div class="copyright">&copy; Imagination Technologies Limited<br> All rights reserved</div>
		</div>
	</div>
</body>

</html>                                                                                                                                                                                                   Client(Control.MousePosition));
        }

        protected override void OnRightToLeftChanged(EventArgs e)
        {
            base.OnRightToLeftChanged(e);
            PerformLayout();
        }
    }
}

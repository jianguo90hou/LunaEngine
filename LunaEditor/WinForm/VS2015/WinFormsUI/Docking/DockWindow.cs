        .text$mn             :�      .debug$S       �              .text$di    	         *�2A     .debug$S    
   �          	    .text$yd             ��     .debug$S       �              _atexit                             &              K               o               �       	        �           .bss                                �           .CRT$XCU                           �             ?qInitResources_lunaeditor@@YAHXZ ?qCleanupResources_lunaeditor@@YAHXZ ??0initializer@?A0x0990e0e1@@QAE@XZ ??1initializer@?A0x0990e0e1@@QAE@XZ ??__Edummy@?A0x0990e0e1@@YAXXZ ??__Fdummy@?A0x0990e0e1@@YAXXZ ?dummy@?A0x0990e0e1@@3Uinitializer@1@A _dummy$initializer$                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 else if (!Visible)
            {
                Visible = true;
                VisibleNestedPanes.Refresh();
            }

            base.OnLayout (levent);
        }

        #region ISplitterDragSource Members

        void ISplitterDragSource.BeginDrag(Rectangle rectSplitter)
        {
        }

        void ISplitterDragSource.EndDrag()
        {
        }

        bool ISplitterDragSource.IsVertical
        {
            get { return (DockState == DockState.DockLeft || DockState == DockState.DockRight); }
        }

        Rectangle ISplitterDragSource.DragLimitBounds
        {
            get
            {
                Rectangle rectLimit = DockPanel.DockArea;
                Point location;
                if ((Control.ModifierKeys & Keys.Shift) == 0)
                    location = Location;
                else
                    location = DockPanel.DockArea.Location;

                if (((ISplitterDragSource)this).IsVertical)
                {
                    rectLimit.X += MeasurePane.MinSize;
                    rectLimit.Width -= 2 * MeasurePane.MinSize;
                    rectLimit.Y = location.Y;
                    if ((Control.ModifierKeys & Keys.Shift) == 0)
                        rectLimit.Height = Height;
                }
                else
                {
                    rectLimit.Y += MeasurePane.MinSize;
                    rectLimit.Height -= 2 * MeasurePane.MinSize;
                    rectLimit.X = location.X;
                    if ((Control.ModifierKeys & Keys.Shift) == 0)
                        rectLimit.Width = Width;
                }

                return DockPanel.RectangleToScreen(rectLimit);
            }
        }

        void ISplitterDragSource.MoveSplitter(int offset)
        {
            if ((Control.ModifierKeys & Keys.Shift) != 0)
                SendToBack();

            Rectangle rectDockArea = DockPanel.DockArea;
            if (DockState == DockState.DockLeft && rectDockArea.Width > 0)
            {
                if (DockPanel.DockLeftPortion > 1)
                    DockPanel.DockLeftPortion = Width + offset;
                else
                    DockPanel.DockLeftPortion += ((double)offset) / (double)rectDockArea.Width;
            }
            else if (DockState == DockState.DockRight && rectDockArea.Width > 0)
            {
                if (DockPanel.DockRightPortion > 1)
                    DockPanel.DockRightPortion = Width - offset;
                else
                    DockPanel.DockRightPortion -= ((double)offset) / (double)rectDockArea.Width;
            }
            else if (DockState == DockState.DockBottom && rectDockArea.Height > 0)
            {
                if (DockPanel.DockBottomPortion > 1)
                    DockPanel.DockBottomPortion = Height - offset;
                else
                    DockPanel.DockBottomPortion -= ((double)offset) / (double)rectDockArea.Height;
            }
            else if (DockState == DockState.DockTop && rectDockArea.Height > 0)
            {
                if (DockPanel.DockTopPortion > 1)
                    DockPanel.DockTopPortion = Height + offset;
                else
                    DockPanel.DockTopPortion += ((double)offset) / (double)rectDockArea.Height;
            }
        }

        #region IDragSource Members

        Control IDragSource.DragControl
        {
            get { return this; }
        }

        #endregion
        #endregion
    }

    /// <summary>
    /// Dock window of Visual Studio 2003/2005 theme.
    /// </summary>
    [ToolboxItem(false)]
    internal class DefaultDockWindow : DockWindow
    {
        internal DefaultDockWindow(DockPanel dockPanel, DockState dockState) : base(dockPanel, dockState)
        {
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            // if DockWindow is document, draw the border
            if (DockState == DockState.Document)
                e.Graphics.DrawRectangle(SystemPens.ControlDark, ClientRectangle.X, ClientRectangle.Y, ClientRectangle.Width - 1, ClientRectangle.Height - 1);

            base.OnPaint(e);
        }
    }
}

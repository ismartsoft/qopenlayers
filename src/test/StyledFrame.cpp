#include "StyledFrame.h"

StyledFrame::StyledFrame(QWidget *parent)
    : QFrame(parent)
{
    setFrameShadow(QFrame::Raised);
    setFrameShape(QFrame::StyledPanel);
}

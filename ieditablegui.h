#ifndef IEDITABLEGUI_H
#define IEDITABLEGUI_H


class IEditableGUI
{
public:

    IEditableGUI();
    virtual void launchEditMode() = 0;

    virtual ~IEditableGUI(){}

};

#endif // IEDITABLEGUI_H

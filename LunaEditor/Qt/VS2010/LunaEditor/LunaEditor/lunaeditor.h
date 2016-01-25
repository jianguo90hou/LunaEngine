#ifndef LUNAEDITOR_H
#define LUNAEDITOR_H

#include <QtWidgets/QMainWindow>
#include "ui_lunaeditor.h"

class LunaEditor : public QMainWindow
{
	Q_OBJECT

public:
	LunaEditor(QWidget *parent = 0);
	~LunaEditor();

private:
	Ui::LunaEditorClass ui;
};

#endif // LUNAEDITOR_H

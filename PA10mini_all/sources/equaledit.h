#ifndef EQUALEDIT_H
#define EQUALEDIT_H

#include <QPlainTextEdit>
#include <QPainter>
#include <QTextBlock>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

class EqualEdit : public QPlainTextEdit
{
	Q_OBJECT

public:
	EqualEdit(QWidget *parent = 0);

	void lineNumberAreaPaintEvent(QPaintEvent *event);
	int lineNumberAreaWidth();
	QString getFileName();

public slots:
	void open();
	void save();
	void saveAs();
	void createNew();
	void textWasChanged();

protected:
	void resizeEvent(QResizeEvent *event);

private slots:
	void updateLineNumberAreaWidth(int newBlockCount);
	void highlightCurrentLine();
	void updateLineNumberArea(const QRect &, int);

private:
	QWidget *lineNumberArea;
	QString fileName;
	bool wasChanged;
};

class LineNumberArea : public QWidget
{
public:
	LineNumberArea(EqualEdit *editor) : QWidget(editor)
	{
		EqualEdit = editor;
	}

	QSize sizeHint() const {
		return QSize(EqualEdit->lineNumberAreaWidth(), 0);
	}

protected:
	void paintEvent(QPaintEvent *event)
	{
		EqualEdit->lineNumberAreaPaintEvent(event);
	}

private:
	EqualEdit *EqualEdit;
};
#endif // EQUALEDIT_H

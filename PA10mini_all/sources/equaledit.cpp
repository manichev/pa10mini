#include "equaledit.h"

EqualEdit::EqualEdit(QWidget *parent) : QPlainTextEdit(parent)
{
    lineNumberArea = new LineNumberArea(this);

    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));

    updateLineNumberAreaWidth(0);
    highlightCurrentLine();

    fileName = QString("default");
    wasChanged = false;
}

int EqualEdit::lineNumberAreaWidth()
{
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10)
    {
        max /= 10;
        ++digits;
    }
    int space = 3 + fontMetrics().width(QLatin1Char('9')) * digits;
    return space;
}

void EqualEdit::updateLineNumberAreaWidth(int /* newBlockCount */)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void EqualEdit::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}

QString EqualEdit::getFileName()
{
    return fileName;
}

void EqualEdit::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void EqualEdit::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly())
    {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(180,230,110).lighter(150);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}

void EqualEdit::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), Qt::lightGray);
    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();

    while (block.isValid() && top <= event->rect().bottom())
    {
        if (block.isVisible() && bottom >= event->rect().top())
        {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::black);
            painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(),
                      Qt::AlignRight, number);
        }
        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }
}

void EqualEdit::createNew()
{
    if (wasChanged)
    {
        QMessageBox msgBox;
        msgBox.setText("Do you want to save changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();

        switch (ret)
        {
        case QMessageBox::Save:
            save();
            break;
        case QMessageBox::Discard:
            break;
        case QMessageBox::Cancel:
            return;
            break;
        }
    }
    fileName = QString("default");
    wasChanged = false;
    clear();
}

void EqualEdit::open()
{
    if (wasChanged) {
        QMessageBox msgBox;
        msgBox.setText("Do you want to save changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();

        switch (ret)
        {
        case QMessageBox::Save:
            save();
            break;
        case QMessageBox::Discard:
            break;
        case QMessageBox::Cancel:
            return;
            break;
        }
    }
    fileName = QFileDialog::getOpenFileName(this, tr("Открыть файл"), "tests", tr("(*.*)"));
    QFile txtFile(fileName);
    if (!txtFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&txtFile);
    clear();
    setUndoRedoEnabled(false);
    while (!in.atEnd()) {
        QString line = in.readLine();
        appendPlainText(line);
    }
    txtFile.close();
    setUndoRedoEnabled(true);
    wasChanged = false;
}

void EqualEdit::textWasChanged()
{
    wasChanged = true;
}

void EqualEdit::saveAs()
{
    fileName = QFileDialog::getSaveFileName(this, tr("Сохранить файл как"), "", tr("(*.txt)"));
    QFile txtFile(fileName);
    if (!txtFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream out(&txtFile);
    out << toPlainText();
    txtFile.close();
    wasChanged = false;
}

void EqualEdit::save()
{
    if (fileName == "default")
        fileName = QFileDialog::getSaveFileName(this, tr("Сохранить файл как"), "", tr("(*.txt)"));
    QFile txtFile(fileName);
    if (!txtFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream out(&txtFile);
    out << toPlainText();
    txtFile.close();
    wasChanged = false;
}

LineNumberArea::LineNumberArea(EqualEdit *editor) : QWidget(editor)
{
    m_EqualEdit = editor;
}

QSize LineNumberArea::sizeHint() const {
    return QSize(m_EqualEdit->lineNumberAreaWidth(), 0);
}

void LineNumberArea::paintEvent(QPaintEvent *event)
{
    m_EqualEdit->lineNumberAreaPaintEvent(event);
}

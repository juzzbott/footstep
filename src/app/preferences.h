#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QDialog>
#include <QLineEdit>

namespace Ui {
class Preferences;
}

class Preferences : public QDialog
{
    Q_OBJECT

public:
    explicit Preferences(QWidget *parent = 0);
    ~Preferences();

public slots:
    void browseProfileDirectory();

private:
    Ui::Preferences *ui;

    QLineEdit _txtProfileDirectory;
};

#endif // PREFERENCES_H

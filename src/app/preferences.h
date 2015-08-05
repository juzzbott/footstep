#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QDialog>
#include <QLineEdit>
#include <QRadioButton>
#include <QSpinBox>

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
    QRadioButton _rdoDecimal;
    QRadioButton _rdoDegrees;
    QRadioButton _rdoDiskMemoryCache;
    QRadioButton _rdoNoCache;
    QSpinBox _spnCacheExpiry;

};

#endif // PREFERENCES_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

class QPushButton;
class QLabel;
class QProgressBar;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;

private slots:

    // File operations
    void onBrowse();

    // Key operations
    void onGenerateKeys();

    // Encryption operations
    void onEncrypt();
    void onDecrypt();

    // Signature operations
    void onSign();
    void onVerify();

private:

    // Buttons
    QPushButton* browseButton;
    QPushButton* encryptButton;
    QPushButton* decryptButton;
    QPushButton* generateKeysButton;
    QPushButton* signButton;
    QPushButton* verifyButton;

    // Progress bar
    QProgressBar* progressBar;

    // Labels
    QLabel* fileLabel;
    QLabel* statusLabel;

    // Selected file path
    QString selectedFile;
};

#endif // MAINWINDOW_H
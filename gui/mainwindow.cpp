#include "mainwindow.h"

#include "asymmetric.hpp"
#include "hybrid.hpp"
#include "keymanager.hpp"
#include "filehandler.hpp"
#include "signature.hpp"

#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <QProgressBar>
#include <QDebug>
#include <iostream>
#include <vector>
#include <string>
#include <QInputDialog>   
#include <QLineEdit>

static const std::string KEY_DIR =
    "/home/kishan/QSecureLib/build/";

static const std::string KEM_PUBLIC_KEY =
    KEY_DIR + "alice.pub";

static const std::string KEM_PRIVATE_KEY =
    KEY_DIR + "alice.priv.enc";

static const std::string SIGN_PUBLIC_KEY =
    KEY_DIR + "sign.pub";

static const std::string SIGN_PRIVATE_KEY =
    KEY_DIR + "sign.priv.enc";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget* centralWidget =
        new QWidget(this);

    auto* layout =
        new QVBoxLayout;

    browseButton =
        new QPushButton("Browse File");

    encryptButton =
        new QPushButton("Encrypt");

    decryptButton =
        new QPushButton("Decrypt");

    generateKeysButton =
        new QPushButton("Generate Keys");

    signButton =
        new QPushButton("Sign File");

    verifyButton =
        new QPushButton("Verify File");

    fileLabel =
        new QLabel("No file selected");

    statusLabel =
        new QLabel("Ready");

    progressBar =
        new QProgressBar;

    progressBar->setRange(0, 100);
    progressBar->setValue(0);

    layout->addWidget(fileLabel);
    layout->addWidget(browseButton);

    layout->addWidget(encryptButton);
    layout->addWidget(decryptButton);

    layout->addWidget(generateKeysButton);

    layout->addWidget(signButton);
    layout->addWidget(verifyButton);

    layout->addWidget(progressBar);
    layout->addWidget(statusLabel);

    centralWidget->setLayout(layout);

    setCentralWidget(centralWidget);

    setWindowTitle("QSecure");

    resize(600, 300);

    connect(
        browseButton,
        &QPushButton::clicked,
        this,
        &MainWindow::onBrowse
    );

    connect(
        generateKeysButton,
        &QPushButton::clicked,
        this,
        &MainWindow::onGenerateKeys
    );

    connect(
        encryptButton,
        &QPushButton::clicked,
        this,
        &MainWindow::onEncrypt
    );

    connect(
        decryptButton,
        &QPushButton::clicked,
        this,
        &MainWindow::onDecrypt
    );

    connect(
        signButton,
        &QPushButton::clicked,
        this,
        &MainWindow::onSign
    );

    connect(
        verifyButton,
        &QPushButton::clicked,
        this,
        &MainWindow::onVerify
    );
}

void MainWindow::onBrowse()
{
    selectedFile =
        QFileDialog::getOpenFileName(
            this,
            "Select File"
        );

    if(selectedFile.isEmpty())
        return;

    fileLabel->setText(selectedFile);

    statusLabel->setText(
        "File selected"
    );
}

void MainWindow::onGenerateKeys()
{
    progressBar->setValue(0);

    statusLabel->setText(
        "Generating keys..."
    );

    bool okPassword = false;

    QString password =
        QInputDialog::getText(
            this,
            "Create Password",
            "Protect your private keys:",
            QLineEdit::Password,
            "",
            &okPassword
        );

    if(!okPassword || password.isEmpty())
    {
        QMessageBox::warning(
            this,
            "Error",
            "Password required"
        );
        return;
    }

    std::vector<unsigned char> kemPublicKey;
    std::vector<unsigned char> kemPrivateKey;

    bool kemOk =
        AsymmetricCrypto::generateKeyPair(
            kemPublicKey,
            kemPrivateKey
        );

    if(!kemOk)
    {
        QMessageBox::critical(
            this,
            "Error",
            "ML-KEM key generation failed"
        );
        return;
    }

   KeyManager::saveKey(
    KEM_PUBLIC_KEY,
    kemPublicKey
);

KeyManager::saveEncryptedKey(
    KEM_PRIVATE_KEY,
    kemPrivateKey,
    password.toStdString()
);
    progressBar->setValue(50);

    std::vector<unsigned char> signPublicKey;
    std::vector<unsigned char> signPrivateKey;

    bool signOk =
        Signature::generateKeyPair(
            signPublicKey,
            signPrivateKey
        );

    if(!signOk)
    {
        QMessageBox::critical(
            this,
            "Error",
            "ML-DSA key generation failed"
        );
        return;
    }

    KeyManager::saveKey(
    SIGN_PUBLIC_KEY,
    signPublicKey
);

KeyManager::saveEncryptedKey(
    SIGN_PRIVATE_KEY,
    signPrivateKey,
    password.toStdString()
);

    progressBar->setValue(100);

    statusLabel->setText(
        "Keys generated successfully"
    );

    QMessageBox::information(
        this,
        "Success",
        "Keys saved:\n\n"
        "alice.pub\n"
        "alice.priv.enc\n"
        "sign.pub\n"
        "sign.priv.enc"
    );
}

void MainWindow::onEncrypt()
{
    if(selectedFile.isEmpty())
    {
        QMessageBox::warning(
            this,
            "Error",
            "Select a file first"
        );
        return;
    }

    auto publicKey =
       KeyManager::loadKey(
         KEM_PUBLIC_KEY
);

    if(publicKey.empty())
    {
        QMessageBox::warning(
            this,
            "Error",
            "Generate keys first"
        );
        return;
    }

    std::string outputFile =
        selectedFile.toStdString()
        + ".qsec";

    bool ok =
        HybridCrypto::encryptFile(
            selectedFile.toStdString(),
            outputFile,
            publicKey
        );

    if(ok)
    {
        QMessageBox::information(
            this,
            "Success",
            QString(
                "Encrypted:\n%1"
            ).arg(
                QString::fromStdString(
                    outputFile
                )
            )
        );
    }
}

void MainWindow::onDecrypt()
{
    if(selectedFile.isEmpty())
    {
        QMessageBox::warning(
            this,
            "Error",
            "Select a .qsec file"
        );
        return;
    }

    bool okPassword = false;

    QString password =
    QInputDialog::getText(
        this,
        "Password",
        "Enter private key password:",
        QLineEdit::Password,
        "",
        &okPassword
    );

if(!okPassword)
    return;

    auto privateKey =
        KeyManager::loadEncryptedKey(
            KEM_PRIVATE_KEY,
            password.toStdString()
        );
    if(privateKey.empty())
    {
        QMessageBox::warning(
            this,
            "Error",
            "Invalid password or private key not found"
        );
        return;
    }

// Generate the original output filename by removing ".qsec"
std::string outputFile = selectedFile.toStdString();

if (outputFile.size() < 5 ||
    outputFile.substr(outputFile.size() - 5) != ".qsec")
{
    QMessageBox::warning(
        this,
        "Error",
        "Please select a valid .qsec file."
    );
    return;
}

// Remove the ".qsec" extension
outputFile.erase(outputFile.size() - 5);

bool ok =
    HybridCrypto::decryptFile(
        selectedFile.toStdString(),
        outputFile,
        privateKey
    );

    if(ok)
    {
        QMessageBox::information(
            this,
            "Success",
            QString(
                "Decrypted:\n%1"
            ).arg(
                QString::fromStdString(
                    outputFile
                )
            )
        );
    }
}

void MainWindow::onSign()
{
    if(selectedFile.isEmpty())
    {
        QMessageBox::warning(
            this,
            "Error",
            "Select a file first"
        );
        return;
    }

    bool okPassword = false;

QString password =
    QInputDialog::getText(
        this,
        "Password",
        "Enter signing key password:",
        QLineEdit::Password,
        "",
        &okPassword
    );

if(!okPassword)
    return;

auto privateKey =
    KeyManager::loadEncryptedKey(
    SIGN_PRIVATE_KEY,
    password.toStdString()
);

    if(privateKey.empty())
    {
        QMessageBox::warning(
            this,
            "Error",
            "Invalid password or signing key not found"
        );
        return;
    }

    auto fileData =
        FileHandler::readFile(
            selectedFile.toStdString()
        );

    if(fileData.empty())
    {
        QMessageBox::warning(
            this,
            "Error",
            "Unable to read file"
        );
        return;
    }

    std::vector<unsigned char> signature;

    bool ok =
        Signature::sign(
            fileData,
            privateKey,
            signature
        );

    if(!ok)
    {
        QMessageBox::critical(
            this,
            "Error",
            "Signing failed"
        );
        return;
    }

    std::string sigFile =
        selectedFile.toStdString() + ".sig";

    std::cout
        << "Saving signature to: "
        << sigFile
        << std::endl;

    bool saved =
        FileHandler::writeFile(
            sigFile,
            signature
        );

    std::cout
        << "Save result = "
        << saved
        << std::endl;

    if(!saved)
    {
        QMessageBox::critical(
            this,
            "Error",
            "Unable to save signature"
        );
        return;
    }

    statusLabel->setText(
        "File signed successfully"
    );

    QMessageBox::information(
        this,
        "Success",
        QString(
            "Signature saved as:\n%1.sig"
        ).arg(selectedFile)
    );
}

void MainWindow::onVerify()
{
    if(selectedFile.isEmpty())
    {
        QMessageBox::warning(
            this,
            "Error",
            "Select a file first"
        );
        return;
    }

    auto publicKey =
       KeyManager::loadKey(
    SIGN_PUBLIC_KEY
    );

    if(publicKey.empty())
    {
        QMessageBox::warning(
            this,
            "Error",
            "sign.pub not found"
        );
        return;
    }

    auto data =
        FileHandler::readFile(
            selectedFile.toStdString()
        );

    if(data.empty())
    {
        QMessageBox::warning(
            this,
            "Error",
            "Unable to read file"
        );
        return;
    }

    std::string sigFile =
        selectedFile.toStdString() + ".sig";

    auto signature =
        FileHandler::readFile(
            sigFile
        );

    if(signature.empty())
    {
        QMessageBox::warning(
            this,
            "Error",
            QString(
                "Signature file not found:\n%1"
            ).arg(
                QString::fromStdString(
                    sigFile
                )
            )
        );
        return;
    }

    bool valid =
        Signature::verify(
            data,
            publicKey,
            signature
        );

    if(valid)
    {
        statusLabel->setText(
            "Signature VALID"
        );

        QMessageBox::information(
            this,
            "Verification",
            "Signature VALID"
        );
    }
    else
    {
        statusLabel->setText(
            "Signature INVALID"
        );

        QMessageBox::critical(
            this,
            "Verification",
            "Signature INVALID"
        );
    }
}

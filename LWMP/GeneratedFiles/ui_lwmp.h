/********************************************************************************
** Form generated from reading UI file 'lwmp.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LWMP_H
#define UI_LWMP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LWMPClass
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *m_btnSelectFolder;
    QPushButton *m_btnStartStopResume;
    QPushButton *m_btnNext;
    QPushButton *m_btnPrevious;
    QComboBox *m_cbFolderList;
    QSlider *m_hsVolume;
    QCheckBox *m_cbShuffle;
    QLabel *m_lblInitialised;
    QListWidget *m_lwTitleList;
    QListWidget *m_lwInitialised;

    void setupUi(QWidget *LWMPClass)
    {
        if (LWMPClass->objectName().isEmpty())
            LWMPClass->setObjectName(QStringLiteral("LWMPClass"));
        LWMPClass->resize(600, 401);
        LWMPClass->setToolTipDuration(5);
        gridLayoutWidget = new QWidget(LWMPClass);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 10, 581, 381));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        m_btnSelectFolder = new QPushButton(gridLayoutWidget);
        m_btnSelectFolder->setObjectName(QStringLiteral("m_btnSelectFolder"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_btnSelectFolder->sizePolicy().hasHeightForWidth());
        m_btnSelectFolder->setSizePolicy(sizePolicy);
        m_btnSelectFolder->setFlat(false);

        gridLayout->addWidget(m_btnSelectFolder, 0, 5, 1, 1);

        m_btnStartStopResume = new QPushButton(gridLayoutWidget);
        m_btnStartStopResume->setObjectName(QStringLiteral("m_btnStartStopResume"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_btnStartStopResume->sizePolicy().hasHeightForWidth());
        m_btnStartStopResume->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(m_btnStartStopResume, 3, 2, 1, 1);

        m_btnNext = new QPushButton(gridLayoutWidget);
        m_btnNext->setObjectName(QStringLiteral("m_btnNext"));
        sizePolicy1.setHeightForWidth(m_btnNext->sizePolicy().hasHeightForWidth());
        m_btnNext->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(m_btnNext, 3, 3, 1, 1);

        m_btnPrevious = new QPushButton(gridLayoutWidget);
        m_btnPrevious->setObjectName(QStringLiteral("m_btnPrevious"));
        sizePolicy1.setHeightForWidth(m_btnPrevious->sizePolicy().hasHeightForWidth());
        m_btnPrevious->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(m_btnPrevious, 3, 1, 1, 1);

        m_cbFolderList = new QComboBox(gridLayoutWidget);
        m_cbFolderList->setObjectName(QStringLiteral("m_cbFolderList"));
        sizePolicy1.setHeightForWidth(m_cbFolderList->sizePolicy().hasHeightForWidth());
        m_cbFolderList->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(m_cbFolderList, 0, 0, 1, 5);

        m_hsVolume = new QSlider(gridLayoutWidget);
        m_hsVolume->setObjectName(QStringLiteral("m_hsVolume"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(m_hsVolume->sizePolicy().hasHeightForWidth());
        m_hsVolume->setSizePolicy(sizePolicy2);
        m_hsVolume->setToolTipDuration(10);
        m_hsVolume->setMaximum(128);
        m_hsVolume->setSingleStep(1);
        m_hsVolume->setValue(100);
        m_hsVolume->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(m_hsVolume, 3, 4, 1, 2);

        m_cbShuffle = new QCheckBox(gridLayoutWidget);
        m_cbShuffle->setObjectName(QStringLiteral("m_cbShuffle"));

        gridLayout->addWidget(m_cbShuffle, 3, 0, 1, 1);

        m_lblInitialised = new QLabel(gridLayoutWidget);
        m_lblInitialised->setObjectName(QStringLiteral("m_lblInitialised"));

        gridLayout->addWidget(m_lblInitialised, 1, 5, 1, 1);

        m_lwTitleList = new QListWidget(gridLayoutWidget);
        m_lwTitleList->setObjectName(QStringLiteral("m_lwTitleList"));

        gridLayout->addWidget(m_lwTitleList, 1, 0, 2, 5);

        m_lwInitialised = new QListWidget(gridLayoutWidget);
        m_lwInitialised->setObjectName(QStringLiteral("m_lwInitialised"));
        QSizePolicy sizePolicy3(QSizePolicy::Ignored, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(m_lwInitialised->sizePolicy().hasHeightForWidth());
        m_lwInitialised->setSizePolicy(sizePolicy3);

        gridLayout->addWidget(m_lwInitialised, 2, 5, 1, 1);


        retranslateUi(LWMPClass);

        m_btnSelectFolder->setDefault(false);


        QMetaObject::connectSlotsByName(LWMPClass);
    } // setupUi

    void retranslateUi(QWidget *LWMPClass)
    {
        LWMPClass->setWindowTitle(QApplication::translate("LWMPClass", "LWMP", Q_NULLPTR));
        m_btnSelectFolder->setText(QApplication::translate("LWMPClass", "select folder", Q_NULLPTR));
        m_btnStartStopResume->setText(QApplication::translate("LWMPClass", "Pause", Q_NULLPTR));
        m_btnNext->setText(QApplication::translate("LWMPClass", "Next", Q_NULLPTR));
        m_btnPrevious->setText(QApplication::translate("LWMPClass", "Previous", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        m_hsVolume->setToolTip(QApplication::translate("LWMPClass", "volume: 100", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        m_cbShuffle->setText(QApplication::translate("LWMPClass", "shuffle", Q_NULLPTR));
        m_lblInitialised->setText(QApplication::translate("LWMPClass", "Initialsed", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LWMPClass: public Ui_LWMPClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LWMP_H

#include "systeminfowidget.h"
#include "systeminfomodel.h"
#include "fontlabel.h"

#include <QHBoxLayout>
#include <QPainter>
#include <QDebug>

using namespace dtb;
using namespace dtb::widgets;
using namespace dtb::systeminfo;

SystemInfoWidget::SystemInfoWidget(QWidget *parent)
    : ContentModule(parent)
{
    setObjectName("SystemInfoWidget");

    setFixedWidth(80);

    m_tx = new QLabel;
    m_tx->setFixedHeight(12);
    m_tx->setText(converSpeed(0));
    m_tx->setStyleSheet("QLabel { font-size: 12px; }");

    m_rx = new QLabel;
    m_rx->setFixedHeight(12);
    m_rx->setText(converSpeed(0));
    m_rx->setStyleSheet("QLabel { font-size: 12px; }");

    FontLabel *up = new FontLabel;
    up->setIcon(QChar(0xE935), 12);

    QHBoxLayout *uploadlayout = new QHBoxLayout;
    uploadlayout->setMargin(0);
    uploadlayout->setSpacing(0);
    uploadlayout->addWidget(up, 0, Qt::AlignVCenter | Qt::AlignLeft);
    uploadlayout->addWidget(m_tx, 0, Qt::AlignVCenter | Qt::AlignRight);

    FontLabel *down = new FontLabel;
    down->setIcon(QChar(0xE936), 12);

    QHBoxLayout *downlayout = new QHBoxLayout;
    downlayout->setMargin(0);
    downlayout->setSpacing(0);
    downlayout->addWidget(down, 0, Qt::AlignVCenter | Qt::AlignLeft);
    downlayout->addWidget(m_rx, 0, Qt::AlignVCenter | Qt::AlignRight);

    QVBoxLayout *mainlayout = new QVBoxLayout;
    mainlayout->setMargin(0);
    mainlayout->setSpacing(2);
    mainlayout->setContentsMargins(3, 0, 3, 0);
    mainlayout->addLayout(uploadlayout);
    mainlayout->addLayout(downlayout);

    setLayout(mainlayout);
}

void SystemInfoWidget::setModel(SystemInfoModel *model)
{
    m_model = model;

    connect(model, &SystemInfoModel::networkSpeedChanged, this, [=] (const quint64 tx, const quint64 rx) {
        m_tx->setText(converSpeed(tx));
        m_rx->setText(converSpeed(rx));
    });
}

const QString SystemInfoWidget::converSpeed(const int value)
{
    if (!value)
        return "0.0 B";

    QString speed;

    for (;;) {
        if (value < 1024) {
            speed = QString::number(value) + " B/s";
            break;
        }
        if (value / 1024 < 1024) {
            speed = QString::number(value / 1024) + " KB/s";
            break;
        }
        if (value / 1024 / 1024 < 1024) {
            speed = QString::number(value / 1024 / 1024) + " MB/s";
            break;
        }
        if (value / 1024 / 1024 / 1024 < 1024) {
            speed = QString::number(value / 1024 / 1024 / 1024) + " GB/s";
            break;
        }
    }

    return speed;
}

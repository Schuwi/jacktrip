//*****************************************************************
/*
  QJackTrip: Bringing a graphical user interface to JackTrip, a
  system for high quality audio network performance over the
  internet.

  Copyright (c) 2020 Aaron Wyatt.

  This file is part of QJackTrip.

  QJackTrip is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  QJackTrip is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with QJackTrip.  If not, see <https://www.gnu.org/licenses/>.
*/
//*****************************************************************

#include "messageDialog.h"

#include "ui_messageDialog.h"
#include <iostream>

MessageDialog::MessageDialog(QWidget* parent)
    : QDialog(parent), m_ui(new Ui::MessageDialog), m_outBuf(new textbuf)
{
    m_ui->setupUi(this);
    m_outStream.reset(new std::ostream(m_outBuf.data()));
    connect(m_outBuf.data(), &textbuf::outputString, this, &MessageDialog::receiveOutput, Qt::QueuedConnection);
}

QSharedPointer<std::ostream> MessageDialog::getOutputStream()
{
    return m_outStream;
}

void MessageDialog::setRelayStream(std::ostream *relay)
{
    m_outBuf->setOutStream(relay);
}

void MessageDialog::clearOutput()
{
    m_ui->messagesTextEdit->clear();
}

void MessageDialog::receiveOutput(const QString& output)
{
    m_ui->messagesTextEdit->insertPlainText(output);
}

MessageDialog::~MessageDialog() = default;

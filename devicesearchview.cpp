/*
 * Qt BlueZ Manager
 *
 * Copyright (C) 2010 Jose Antonio Santos-Cadenas <santoscadenas at gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "devicesearchview.h"
#include "ui_devicesearchview.h"

#include "adapterview.h"

DeviceSearchView::DeviceSearchView(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DeviceSearchView)
{
	ui->setupUi(this);

	ui->progressBar->setMaximum(1);
	ui->progressBar->setValue(1);

	connect(ui->searchAgain, SIGNAL(clicked()), this, SLOT(searchAgain()));
	connect(ui->pairDevice, SIGNAL(clicked()), this,
						SLOT(pairWithSelected()));
}

DeviceSearchView::~DeviceSearchView()
{
	delete ui;
}

void DeviceSearchView::DeviceDisappeared(const QString &address)
{
	for (int i = 0; i < ui->treeWidget->topLevelItemCount(); i++) {
		QTreeWidgetItem *widget = ui->treeWidget->topLevelItem(i);
		if (widget->text(1) == address) {
			delete ui->treeWidget->takeTopLevelItem(i);
			return;
		}
	}
}

void DeviceSearchView::DeviceFound(const QString &address,
						const QVariantMap &values)
{
	for (int i = 0; i < ui->treeWidget->topLevelItemCount(); i++) {
		QTreeWidgetItem *widget = ui->treeWidget->topLevelItem(i);
		if (widget->text(1) == address) {
			widget->setText(0, values["Name"].toString());
			widget->setText(1, address);
			return;
		}
	}

	QTreeWidgetItem *widget = new QTreeWidgetItem(ui->treeWidget);
	widget->setText(0, values["Name"].toString());
	widget->setText(1, address);
}

void DeviceSearchView::propertyChanged(const QString name,
						const QDBusVariant value)
{
	if (name == "Discovering") {
		if (value.variant().toBool()) {
			ui->progressBar->setMaximum(0);
			ui->progressBar->setValue(0);
		} else {
			ui->progressBar->setMaximum(1);
			ui->progressBar->setValue(1);
			ui->progressBar->setFormat("Search done");
		}
	}
}

void DeviceSearchView::searchAgain()
{
	if (!parent()->parent()->inherits("AdapterView"))
		return;
	AdapterView *adapter = (AdapterView *)parent()->parent();
	adapter->getAdapter()->StartDiscovery();
}

void DeviceSearchView::pairWithSelected()
{
	QList<QTreeWidgetItem *> devices = ui->treeWidget->selectedItems();
	foreach (QTreeWidgetItem *device, devices) {
		qDebug() << "Device selected " << device->text(0);
		//TODO: Pair selected device
	}
}

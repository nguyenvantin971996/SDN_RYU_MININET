﻿#include "MainWindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <QFileDialog>
#include <QTime>

MainWindow::MainWindow(QWidget * parent) :
    QMainWindow(parent), ui(new Ui::MainWindow), openedFilePath(QString())
{
    ui->setupUi(this);
    setupComponents();
    QObject::connect(ui->networkMapView,
                     SIGNAL(signalMouseLeftButtonReleased(QPoint)),
                     this,
                     SLOT(mouseLeftButtonReleaseEventOccured(QPoint)));
    QObject::connect(ui->networkMapView,
                     SIGNAL(signalMouseLeftButtonPressed(QPoint)),
                     this,
                     SLOT(mouseLeftButtonPressEventOccured(QPoint)));
    QObject::connect(ui->networkMapView,
                     SIGNAL(signalMouseMoved(QPoint)),
                     this,
                     SLOT(mouseMoveEventOccured(QPoint)));
    QObject::connect(ui->networkMapView,
                     SIGNAL(signalMouseDoubleClicked(QPoint)),
                     this,
                     SLOT(mouseDoubleClickEvent(QPoint)));
}

void MainWindow::setupComponents()
{
    metricGroupInMenu = new QActionGroup(this);
    toolsGroupInMenu = new QActionGroup(this);
    toolsGroup = new QActionGroup(this);
    metricGroupInMenu->addAction(ui->actionDisplayDelay);
    metricGroupInMenu->addAction(ui->actionDisplayBandwidth);
    metricGroupInMenu->addAction(ui->actionDisplayPacketLoss);
    toolsGroupInMenu->addAction(ui->actionSdnController);
    toolsGroupInMenu->addAction(ui->actionHost);
    toolsGroupInMenu->addAction(ui->actionSwitch);
    toolsGroupInMenu->addAction(ui->actionLink);
    toolsGroupInMenu->addAction(ui->actionEdit);

    setupInstrumentsToolBar();
    setupUtilitiesToolBar();
}

void MainWindow::setupInstrumentsToolBar()
{
    toolsToolBar = new QToolBar("toolsToolBar");
    toolsToolBar->setIconSize(QSize(64, 64));
    actionSdnController = toolsToolBar->addAction(QPixmap(":images/controller.png"), "Controller (C)", this, SLOT(on_actionSdnController_triggered()));
    actionSdnController->setCheckable(true);
    toolsGroup->addAction(actionSdnController);
    actionSwitch = toolsToolBar->addAction(QPixmap(":images/switch.png"), "Switch (S)", this, SLOT(on_actionSwitch_triggered()));
    actionSwitch->setCheckable(true);
    toolsGroup->addAction(actionSwitch);
    actionHost = toolsToolBar->addAction(QPixmap(":images/host.png"), "Host (H)", this, SLOT(on_actionHost_triggered()));
    actionHost->setCheckable(true);
    toolsGroup->addAction(actionHost);
    actionLink = toolsToolBar->addAction(QPixmap(":images/link.png"), "Link (L)", this, SLOT(on_actionLink_triggered()));
    actionLink->setCheckable(true);
    toolsGroup->addAction(actionLink);
    actionText = toolsToolBar->addAction(QPixmap(":images/text.png"), "Text (T)", this, SLOT(on_actionText_triggered()));
    actionText->setCheckable(true);
    toolsGroup->addAction(actionText);
    toolsToolBar->addSeparator();
    actionEdit = toolsToolBar->addAction(QPixmap(":images/edit.png"), "Edit (E)", this, SLOT(on_actionEdit_triggered()));
    actionEdit->setCheckable(true);
    actionEdit->setChecked(true);
    toolsGroup->addAction(actionEdit);
    addToolBar(Qt::LeftToolBarArea, toolsToolBar);
}

void MainWindow::setupUtilitiesToolBar()
{
    utilitiesToolBar = new QToolBar("utilitiesToolBar");
    utilitiesToolBar->setIconSize(QSize(64, 64));
    utilitiesToolBar->addAction(QPixmap(":images/new.png"), "New", this, SLOT(on_actionNew_triggered()));
    utilitiesToolBar->addAction(QPixmap(":images/open.png"), "Open...", this, SLOT(on_actionOpen_triggered()));
    utilitiesToolBar->addAction(QPixmap(":images/save.png"), "Save...", this, SLOT(on_actionSave_triggered()));
    utilitiesToolBar->addAction(QPixmap(":images/save_as.png"), "Save as...", this, SLOT(on_actionSaveAs_triggered()));
    utilitiesToolBar->addAction(QPixmap(":images/python.png"), "Export Mininet Script", this, SLOT(on_actionCreateMnDataFile_triggered()));
    utilitiesToolBar->addSeparator();
    utilitiesToolBar->addAction(QPixmap(":images/fullConnection.png"), "Full Connection", this, SLOT(on_actionMake_Full_Connection_triggered()));
    addToolBar(Qt::RightToolBarArea, utilitiesToolBar);
}

void MainWindow::prepareTerminal()
{
    ui->terminal->clear();
}

QString MainWindow::getFileNameFromOpenedFilePath()
{
    return openedFilePath.split("/").last();
}

void MainWindow::updateWindowTitle()
{
    this->setWindowTitle(QString("SDN Topology [") +
                         getFileNameFromOpenedFilePath() +
                         QString("]"));
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    int keyCode = event->key();
    switch(keyCode)
    {
        case Qt::Key_Delete:
            emit signalHandleKeyDeletePressEvent();
            break;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionSdnController_triggered()
{
    ui->actionSdnController->setChecked(true);
    actionSdnController->setChecked(true);
    emit signalPrepareSdnController();
}

void MainWindow::on_actionHost_triggered()
{
    ui->actionHost->setChecked(true);
    actionHost->setChecked(true);
    emit signalPrepareHost();
}

void MainWindow::on_actionSwitch_triggered()
{
    ui->actionSwitch->setChecked(true);
    actionSwitch->setChecked(true);
    emit signalPrepareSwitch();
}

void MainWindow::on_actionLink_triggered()
{
    ui->actionLink->setChecked(true);
    actionLink->setChecked(true);
    emit signalPrepareLink();
}

void MainWindow::on_actionEdit_triggered()
{
    ui->actionEdit->setChecked(true);
    actionEdit->setChecked(true);
    emit signalChangeStateToEdit();
}

void MainWindow::on_actionText_triggered()
{
    ui->actionText->setChecked(true);
    actionText->setChecked(true);
    emit signalPrepareTextLabel();
}

void MainWindow::on_actionShowPorts_triggered(bool checked)
{
    emit signalShowPorts(checked);
}

void MainWindow::on_actionDisplayDelay_triggered()
{
    emit signalShowDelay();
}

void MainWindow::on_actionDisplayBandwidth_triggered()
{
    emit signalShowBandwidth();
}

void MainWindow::on_actionDisplayPacketLoss_triggered()
{
    emit signalShowPacketLossRate();
}

void MainWindow::on_actionCreateMnDataFile_triggered()
{
    QString filePath = QFileDialog::getSaveFileName(this,
                                                    "Save MiniNet Script",
                                                    "C:/Users/nguye/Desktop/SDN_RYU_MININET/topo.py",
                                                    "Python files (*.py)");
    if (!filePath.isEmpty())
    {
        emit signalCreateMininetScript(filePath);
    }
}

void MainWindow::mouseLeftButtonReleaseEventOccured(QPoint cursorPosition)
{
    emit signalHandleMouseReleaseEvent(cursorPosition);
}

void MainWindow::mouseLeftButtonPressEventOccured(QPoint cursorPosition)
{
    emit signalHandleMousePressEvent(mapFrom(this, cursorPosition));
}

void MainWindow::mouseMoveEventOccured(QPoint cursorPosition)
{
    emit signalHandleMouseMoveEvent(cursorPosition);
}

void MainWindow::mouseDoubleClickEvent(QPoint cursorPosition)
{
    emit signalHandleDoubleClickEvent(cursorPosition);
}

void MainWindow::refreshNetworkMapView(QPixmap image)
{
    ui->networkMapView->refresh(image);
}

void MainWindow::showMessage(QString message)
{
    ui->terminal->append(QTime::currentTime().toString() +
                         QString(" [Controller] ") + message);
}

void MainWindow::on_actionSaveAs_triggered()
{
    openedFilePath = QFileDialog::getSaveFileName(this,
                                                  "Save topology",
                                                  "C:/Users/nguye/Desktop/SDN_RYU_MININET/topology.sdn.xml",
                                                  "Xml files (*.xml)");
    if (!openedFilePath.isEmpty())
    {
        emit signalSaveNetworkMap(openedFilePath);
        updateWindowTitle();
    }
}

void MainWindow::on_actionSave_triggered()
{
    if (openedFilePath.isEmpty())
    {
        on_actionSaveAs_triggered();
    }
    else
    {
        emit signalSaveNetworkMap(openedFilePath);
        updateWindowTitle();
    }
}

void MainWindow::on_actionOpen_triggered()
{
    openedFilePath = QFileDialog::getOpenFileName(this,
                                                  "Open topology file",
                                                  "C:/Users/nguye/Desktop/SDN_RYU_MININET/topology.sdn.xml",
                                                  "Xml files (*.xml)");
    if (!openedFilePath.isEmpty())
    {
        emit signalLoadNetworkMap(openedFilePath);
        updateWindowTitle();
    }
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionMake_Full_Connection_triggered()
{
    emit signalConnectSdnController();
}

void MainWindow::on_actionNew_triggered()
{
    openedFilePath = QString();
    updateWindowTitle();
    emit signalClearNetworkMap();
}

void MainWindow::on_actionWeights_Matrix_triggered()
{
    QString filePath = QFileDialog::getSaveFileName(this,
                                                    "Save Metric Data",
                                                    "C:/Users/nguye/Desktop/SDN_RYU_MININET/metric_data.txt",
                                                    "Text files (*.txt)");
    if (!filePath.isEmpty())
    {
        emit signalCreateWeightMatrix(filePath);
    }
}

void MainWindow::on_actionAlign_Horizontally_triggered()
{
    emit signalAlignHorizontally();
}

void MainWindow::on_actionAlign_Vertically_triggered()
{
    emit signalAlignVertically();
}

void MainWindow::on_actionRemove_Marks_triggered()
{
    emit signalRemoveMarks();
}

void MainWindow::on_actionCreate_optimal_path_triggered()
{
//    QTime dieTime= QTime::currentTime().addSecs(1);
//        while (QTime::currentTime() < dieTime)
//            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    bool dk = true;
    QList<QList<int>> paths;
    QString filename="C:/Users/nguye/Desktop/SDN_RYU_MININET/demo.txt";
        QFile file(filename);
        if(!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(0, "error", file.errorString());
        }
        QTextStream in(&file);
        int i=1;
        while(!in.atEnd()){
            QString line = in.readLine();
            QString pathOutPut = "Path[";
            QString ii = QString::number(i);
            pathOutPut = pathOutPut +ii+"]: ";
            QStringList linelist;
            QList<int> path;
            linelist = line.split(",");
            for(int x=0;x<=linelist.count()-2;x++)
            {
                path.append((linelist.at(x).toInt()));
                pathOutPut=pathOutPut+" "+linelist.at(x);
            }
            if(path.at(path.count()-1) == 5 && path.at(0) == 1)
            {
                pathOutPut=pathOutPut+" with cost: "+linelist.at(linelist.count()-1);
            }
            else
            {
                pathOutPut=pathOutPut +" "+linelist.at(linelist.count()-1);
                dk = false;
            }
            ui->terminal->append(pathOutPut);
            paths.append(path);
            i++;
        }
        ui->terminal->append("==============================================================");
        file.close();
        if(dk){
            emit signalVisualizePaths(paths);
        }
}

void MainWindow::on_actionNN_GA_triggered()
{
    QString pathss = "C:/Users/nguye/Desktop/SDN_RYU_MININET";
       QString  command("python");
       QStringList params = QStringList() << "12_12.py";

       QProcess *process = new QProcess();
       process->startDetached(command, params, pathss);
       process->waitForFinished();
       process->close();
       QMessageBox msgBox;
       msgBox.setText("Prediction path has been finished!!!");
       msgBox.exec();
}


void MainWindow::on_actionRandomMetric_triggered()
{
    emit signalRemoveMarks();
    emit signalRandomMetric();
}


void MainWindow::on_actionNN_GA_8_8_8_triggered()
{
    QString pathss = "C:/Users/nguye/Desktop/SDN_RYU_MININET";
       QString  command("python");
       QStringList params = QStringList() << "NN_GA_8_8_8.py";

       QProcess *process = new QProcess();
       process->startDetached(command, params, pathss);
       process->waitForFinished();
       process->close();
       QMessageBox msgBox;
       msgBox.setText("Prediction path has been finished!!!");
       msgBox.exec();
}


void MainWindow::on_actionNN_ABC_8_8_8_triggered()
{
    QString pathss = "C:/Users/nguye/Desktop/SDN_RYU_MININET";
       QString  command("python");
       QStringList params = QStringList() << "NN_ABC_8_8_8.py";

       QProcess *process = new QProcess();
       process->startDetached(command, params, pathss);
       process->waitForFinished();
       process->close();
       QMessageBox msgBox;
       msgBox.setText("Prediction path has been finished!!!");
       msgBox.exec();
}


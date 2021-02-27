#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "TableModel.h"
#include "TableView.h"
#include "Chart.h"
#include "GraphicsScene.h"
#include <QGraphicsRectItem>
#include <QVXYModelMapper>
#include <QPushButton>
#include <QSqlError>
#include <QSqlRelationalDelegate>
#include "GraphicsView.h"
#include "MySqlTableModel2.h"
#include "databasemanager.h"
#include "TableManager.h"
#include "UserActivityController.h"
#include "DeleteRecord.h"
#include "EditRecord.h"
#include "AddRecord.h"
#include "IdentityProxyModel.h"
#include "Configuration.h"

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>



#include <QImage>
#include <QPixmap>

cv::Mat analyze_image(const cv::Mat& bill);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Configuration config;

    m_manager = new DatabaseManager(config.databaseName);
    ui->comboBoxTables->addItems(m_manager->getTableNames());
    connect(ui->pushButtonDebug, &QPushButton::clicked,this,&MainWindow::slotPushButtonDebugClicked);

    TableManager* tableManager = new TableManager(ui->comboBoxTables,
                                                  ui->tableView,
                                                  ui->tableWidgetNewRecord ,
                                                  m_manager,
                                                  this);

    UserActivityController activityController(ui->tableView,
                                              ui->tableWidgetNewRecord,
                                              ui->pushButton,
                                              ui->comboBoxTables);

    DeleteRecord deleteRecord(m_manager,ui->tableView);

    EditRecord* editRecord = new EditRecord(m_manager,
                                            ui->tableView,
                                            ui->tableWidgetNewRecord,
                                            ui->pushButton);

    AddRecord* addRecord = new AddRecord(m_manager,
                                            ui->tableView,
                                            ui->tableWidgetNewRecord,
                                            ui->pushButton);

    //******************
    // Graph
    //******************
    TableModel* tableModel = new TableModel(this);
    ui->graphicsView->setTableModel(tableModel);

    //******************
    // OpenCv
    //******************
    cv::Mat matrix;
    matrix = cv::imread(config.sampleBillImageName.toStdString());

    // OpenCV always uses BGR color space by default but Qt, uses RGB.
    // Convert the color space to match Qt’s:

    cv::Mat mat2 = analyze_image(matrix);
    cv::cvtColor(mat2,mat2,CV_BGR2RGB);
    cv::resize(mat2, mat2, cv::Size(ui->labelImage->size().width(),
                                        ui->labelImage->size().height()), 0, 0, cv::INTER_LINEAR);




    QImage img = QImage(mat2.data,mat2.cols,mat2.rows,mat2.step,QImage::Format_RGB888);
    ui->labelImage->setPixmap(QPixmap::fromImage(img));
    ui->labelDebug->show();



}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotPushButtonDebugClicked()
{
    Configuration config;
    ui->labelDebug->setText(config.debugTestString);

    cv::Mat matrix;
    //matrix = cv::imread(config.sampleBillImageName.toStdString());
    matrix = cv::imread("C:/Projects/Daric/DaricLib/testData/sampleBill.jpg");

    QString blah = "w = " + QString::number(matrix.size().width) + ", h = " + QString::number(matrix.size().height);
    ui->labelDebug->setText(blah);

    cv::resize(matrix, matrix, cv::Size(ui->labelImage->size().width(),
                                        ui->labelImage->size().height()), 0, 0, cv::INTER_LINEAR);
    // OpenCV always uses BGR color space by default but Qt, uses RGB.
    // Convert the color space to match Qt’s:
    cv::cvtColor(matrix,matrix,CV_BGR2RGB);


    QImage img = QImage(matrix.data,matrix.cols,matrix.rows,matrix.step,QImage::Format_RGB888);
    ui->labelImage->setPixmap(QPixmap::fromImage(img));
    ui->labelDebug->show();

}


cv::Mat analyze_image(const cv::Mat& large)
{
    // Ref: https://stackoverflow.com/questions/23506105/extracting-text-opencv
    cv::Mat rgb;
    // downsample and use it for processing
    cv::pyrDown(large, rgb);
    cv::Mat small;
    cv::cvtColor(rgb, small, CV_BGR2GRAY);
    // morphological gradient
    cv::Mat grad;
    cv::Mat morphKernel = getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(3, 3));
    cv::morphologyEx(small, grad, cv::MORPH_GRADIENT, morphKernel);
    // binarize
    cv::Mat bw;
    cv::threshold(grad, bw, 0.0, 255.0, cv::THRESH_BINARY | cv::THRESH_OTSU);
    // connect horizontally oriented regions
    cv::Mat connected;
    morphKernel = getStructuringElement(cv::MORPH_RECT, cv::Size(19, 1));
    cv::morphologyEx(bw, connected, cv::MORPH_CLOSE, morphKernel);
    // find contours
    cv::Mat mask = cv::Mat::zeros(bw.size(), CV_8UC1);
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(connected, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
    // filter contours
    for(int idx = 0; idx >= 0; idx = hierarchy[idx][0])
    {
        cv::Rect rect = boundingRect(contours[idx]);
        cv::Mat maskROI(mask, rect);
        maskROI = cv::Scalar(0, 0, 0);
        // fill the contour
        drawContours(mask, contours, idx, cv::Scalar(255, 255, 255), CV_FILLED);
        // ratio of non-zero pixels in the filled region
        double r = (double)countNonZero(maskROI)/(rect.width*rect.height);

        if (r > .45 /* assume at least 45% of the area is filled if it contains text */
            &&
            (rect.height > 8 && rect.width > 8) /* constraints on region size */
            /* these two conditions alone are not very robust. better to use something
            like the number of significant peaks in a horizontal projection as a third condition */
            )
        {
            rectangle(rgb, rect, cv::Scalar(0, 255, 0), 2);
        }
    }
    return rgb;
}

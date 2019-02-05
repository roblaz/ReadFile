#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <cmath>
//#include <QDir>

#define MAXPOINTS 10

typedef struct newPoints {
    double x, y;
} newP;

double distance(newP A, newP B); // return distance between point A and B (use Pifagor's Theorem)
double perimeter(newP Array[]); // return distance perimeter usind function distance 4 times
double area(newP Array[]);  // return area using Gauss's area formula or use Geron formaula for two triangles ABC + ACD
double deter(newP A, newP B);

static int iPointsCount = 0;

int main()
{
    //QDir dir(".");
    //qDebug() << dir.absolutePath();

    QString qsRetVal;
    double perim, ar;

    newP np[MAXPOINTS];

    QFile readf("../ReadFile/ExamplePoints.txt"); //need real directory
    if (readf.open(QFile::ReadOnly)) {
        if (readf.exists()) {
            int i;
            QString strTemp;
            QStringList list;

            QTextStream in(&readf);

            qDebug() << endl;

            for (i = 0; (i < MAXPOINTS) & !in.atEnd(); i++) {
                strTemp = in.readLine();

                list = strTemp.split(";");
                np[i].x = list[0].toDouble();
                np[i].y = list[1].toDouble();

                qDebug()  << i + 1 << " Double: x =" << np[i].x << "y =" << np[i].y;
            }
            iPointsCount = i;
        } else {
            qDebug() << "File not exist";
            return 1;
        }
    } else {
        qDebug() << "File can't open";
        return 1;
    }

    qsRetVal = "Have perimeter %1 and area %2";
    perim = perimeter(np);
    ar = area(np);
    qsRetVal = qsRetVal.arg(perim,0,'f',2).arg(ar,0,'f',3);
    qDebug() << qsRetVal;
    qsRetVal += "\n";

    if (readf.exists())
        readf.close();

}

double distance(newP A, newP B)
{
    return sqrt( (A.x-B.x)*(A.x-B.x) + (A.y-B.y)*(A.y-B.y) );
}

double perimeter(newP Array[])
{
    newP A[MAXPOINTS + 1];
    int i=0;
    double ret=0;

    for (; i < iPointsCount; i++)
        A[i]=Array[i];

    A[i]=Array[0];


    for (i=0; i < iPointsCount; i++)
        ret += distance(A[i],A[i+1]);

    return ret;
}

double deter(newP A, newP B)
{
    return ((A.x*B.y) - (A.y*B.x));
}

double area(newP Array[])
{
    newP A[MAXPOINTS + 1];
    int i=0;
    double ret = 0;
    double det=0;

    for (; i < iPointsCount; i++)
        A[i]=Array[i];
    A[i]=Array[0];


    QString qsTemp;

    for (i=0; i < iPointsCount; i++) {
        det = deter(A[i],A[i+1]);
        qsTemp= "Deter for [%1,%2] : [%3,%4] is %5";
        qsTemp= qsTemp.arg(A[i].x).arg(A[i].y).arg(A[i+1].x).arg(A[i+1].y).arg(det);
        qDebug() << qsTemp;
        ret += det;
    }
    return fabs(ret / 2.0);
}

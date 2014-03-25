#include <QApplication>
#include "server.h"


using namespace std;


int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	vacServerDialog *pServer = new vacServerDialog;
	pServer->show();


	return app.exec();
	



}

#include <QApplication>
#include "client.h"

using namespace std;


int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	ClientDialog *client = new ClientDialog;

	client->show();
	return app.exec();
}

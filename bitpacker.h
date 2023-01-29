#include <QByteArray>
#include <iostream>
using namespace std;
class BitPacker {
	QByteArray res;
	quint8 bitsLeft = 8;
	quint8 buf = 0;

public:
	void operator+=(const std::string& s);

	QByteArray finish();
};
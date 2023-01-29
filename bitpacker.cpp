#include <QByteArray>
#include "./inc/bitpacker.h"

void BitPacker ::operator+=(const string& s) {
    for (auto c : s) {
        buf = buf << 1 | c - '0';
        if (--bitsLeft == 0) {
            res.append(buf);
            buf = 0;
            bitsLeft = 8;
        }
    }
}

QByteArray BitPacker::finish() {
    if (bitsLeft < 8) {
        res.append(buf << bitsLeft);
        buf = 0;
        bitsLeft = 8;
    }
    return res;
}
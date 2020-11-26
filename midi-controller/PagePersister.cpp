#include <EEPROM.h>
#include "PagePersister.h"
#include "globals.h"

    void PagePersister::init() {
        int val1 = EEPROM.read(eepromAddress) - eepromOffset;
        int val2 = EEPROM.read(eepromAddress + 1) - eepromOffset; //storing in two cells just for safety (probably overkill ;) )

        if(val1 != val2 || val1 < BASICPAGE || val1 > LOOPER2PAGE)
            update(BASICPAGE);
    }
    int PagePersister::get() {
        return EEPROM.read(eepromAddress) - eepromOffset;
    }
    void PagePersister::update(int pageId) {
        EEPROM.update(eepromAddress, pageId + eepromOffset);
        EEPROM.update(eepromAddress + 1, pageId + eepromOffset);
    }
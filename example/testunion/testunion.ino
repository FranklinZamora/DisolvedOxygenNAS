#include <SensorsNAS.h>

SensorsNAS sensorDO(97);
SensorsNAS sensorPH(99);
SensorsNAS sensorEC(100);

typedef union
{
    uint8_t value;
    uint8_t bytes[1];
} UINT8_t;

typedef union
{
    uint16_t value;
    uint8_t bytes[2];
} UINT16_t;

typedef union
{
    uint32_t value;
    uint8_t bytes[4];
} UINT32_t;

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    UINT32_t EC, TDS;
    UINT16_t DisolvedOx, SaturationOx, Ph, SAL;
    UINT8_t SG;

    DisolvedOx.value = sensorDO.getDO() * 100;
    SaturationOx.value = sensorDO.getSAT() * 100;
    Ph.value = sensorPH.getPH() * 100;
    EC.value = sensorEC.getEC() * 100;
    TDS.value = sensorEC.getTDS() * 100;
    SAL.value = sensorEC.getSAL() * 100;
    SG.value = sensorEC.getSG() * 100;

    uint16_t arrayBytes[35] = {0x7E, 0x00, 0x20, 0x10, 0x00};
    /*
    arrayBytes[0] = 0x7E; // Start
    arrayBytes[1] = 0x00; // length 1
    arrayBytes[2] = 0x20; // Length 2
    arrayBytes[3] = 0x10; // Frametype
    arrayBytes[4] = 0x00; // Frame ID
    */
    arrayBytes[13] = 0xFF; // 8bit Add
    arrayBytes[14] = 0xFE; // 8bit ADD
    arrayBytes[15] = 0x00; // Broadcast radio
    arrayBytes[16] = 0x00; // Option

    arrayBytes[17] = 0x48; // Payload Start

    arrayBytes[18] = DisolvedOx.bytes[1];
    arrayBytes[19] = DisolvedOx.bytes[0];

    arrayBytes[20] = SaturationOx.bytes[1];
    arrayBytes[21] = SaturationOx.bytes[0];

    arrayBytes[22] = Ph.bytes[1];
    arrayBytes[23] = Ph.bytes[0];

    arrayBytes[24] = EC.bytes[3];
    arrayBytes[25] = EC.bytes[2];
    arrayBytes[26] = EC.bytes[1];
    arrayBytes[27] = EC.bytes[0];

    arrayBytes[28] = TDS.bytes[3];
    arrayBytes[29] = TDS.bytes[2];
    arrayBytes[30] = TDS.bytes[1];
    arrayBytes[31] = TDS.bytes[0];

    arrayBytes[32] = SAL.bytes[1];
    arrayBytes[33] = SAL.bytes[0];

    arrayBytes[34] = SG.bytes[0]; // Cksm

    Serial.println("-------------");
    Serial.print(arrayBytes[0], HEX);
    Serial.print(" ");
    Serial.print(arrayBytes[1], HEX);
    Serial.print(" ");

    Serial.print(arrayBytes[2], HEX);
    Serial.print(" ");
    Serial.print(arrayBytes[3], HEX);
    Serial.print(" ");

    Serial.print(arrayBytes[4], HEX);
    Serial.print(" ");
    Serial.print(arrayBytes[5], HEX);
    Serial.print(" ");

    Serial.print(arrayBytes[6], HEX);
    Serial.print(" ");
    Serial.print(arrayBytes[7], HEX);
    Serial.print(" ");
    Serial.print(arrayBytes[8], HEX);
    Serial.print(" ");
    Serial.print(arrayBytes[9], HEX);
    Serial.print(" ");

    Serial.print(arrayBytes[10], HEX);
    Serial.print(" ");
    Serial.print(arrayBytes[11], HEX);
    Serial.print(" ");
    Serial.print(arrayBytes[12], HEX);
    Serial.print(" ");
    Serial.print(arrayBytes[13], HEX);
    Serial.print(" ");

    Serial.print(arrayBytes[14], HEX);
    Serial.print(" ");
    Serial.print(arrayBytes[15], HEX);
    Serial.print(" ");

    Serial.print(arrayBytes[16], HEX);
    Serial.print(" ");

    Serial.print(arrayBytes[17], HEX);
    Serial.print(" ");

    Serial.print(arrayBytes[18], HEX); // PL
    Serial.print(" ");
    Serial.print(arrayBytes[19], HEX);
    Serial.print(" ");

    Serial.print(arrayBytes[20], HEX);
    Serial.print(" ");
    Serial.print(arrayBytes[21], HEX);
    Serial.print(" ");

    Serial.print(arrayBytes[22], HEX);
    Serial.print(" ");
    Serial.print(arrayBytes[23], HEX);
    Serial.print(" ");

    Serial.print(arrayBytes[24], HEX);
    Serial.print(" ");
    Serial.print(arrayBytes[25], HEX);
    Serial.print(" ");
    Serial.print(arrayBytes[26], HEX);
    Serial.print(" ");
    Serial.print(arrayBytes[27], HEX);
    Serial.print(" ");

    Serial.print(arrayBytes[28], HEX);
    Serial.print(" ");
    Serial.print(arrayBytes[29], HEX);
    Serial.print(" ");
    Serial.print(arrayBytes[30], HEX);
    Serial.print(" ");
    Serial.print(arrayBytes[31], HEX);
    Serial.print(" ");

    Serial.print(arrayBytes[32], HEX);
    Serial.print(" ");
    Serial.print(arrayBytes[33], HEX);
    Serial.print(" ");

    Serial.print(arrayBytes[34], HEX);
    Serial.print(" ");

    Serial.print(arrayBytes[35], HEX); // CKSM
    Serial.print(" ");

    Serial.println();
    Serial.println("-------------");
}

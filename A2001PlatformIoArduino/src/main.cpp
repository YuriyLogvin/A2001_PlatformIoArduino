#include <Arduino.h>

#include <EmKitRs485InterfaceDisplay.h>

#include <lcd.h>
#include "gui.h"
#include <GObjs/GObjText.h>
#include <GObjs/GObjKeyValue.h>
#include <defaultheader.h>
#include <Fonts/FontVenator24.h>

#define UsedFont FontVenator24
GObjPicStretched* _BarMain = NULL;
GObjText* _GuiMainCaption = NULL;

GObjKeyValue* _GuiSoc = NULL;  
GObjKeyValue* _GuiVoltage = NULL;  
GObjKeyValue* _GuiCurrent = NULL;  
GObjKeyValue* _GuiDischargeState = NULL;  
GObjKeyValue* _GuiChargeState = NULL;  
GObjKeyValue* _GuiCellMinV = NULL;  
GObjKeyValue* _GuiCellMaxV = NULL;  
GObjKeyValue* _GuiCellMinT = NULL;  
GObjKeyValue* _GuiCellMaxT = NULL;  


EmKitRs485InterfaceDisplay* _EmKitRs485InterfaceDisplay = NULL;
uint32_t _Rs485TxEnPin = PA1;

void _PrintCellVoltage(const Cell& lci, char* buff);
void _PrintCellTemp(const Cell& lci, char* buff);

void _LcdPinsInit()
{
  pinMode(PA8, OUTPUT);
  pinMode(PA9, OUTPUT);
  pinMode(PB0, OUTPUT);
  pinMode(PB1, OUTPUT);
  pinMode(PB2, OUTPUT);
  pinMode(PB3, OUTPUT);
  pinMode(PB4, OUTPUT);
  pinMode(PB5, OUTPUT);
  pinMode(PB6, OUTPUT);
  pinMode(PB7, OUTPUT);
  pinMode(PC13, OUTPUT);
  pinMode(PC14, OUTPUT);
  pinMode(PC15, OUTPUT);
}

Cell _CellMinV;
Cell _CellMaxV;
Cell _CellMinT;
Cell _CellMaxT;

void setup() {

  _EmKitRs485InterfaceDisplay = new EmKitRs485InterfaceDisplay(&Serial, _Rs485TxEnPin);

  _CellMinV.No = 0xff;

  _LcdPinsInit();
  LCD_Init();

  _BarMain = new GObjPicStretched(Canvas(0,0,320,480), (const ImgHeaderPixel*)_ImgHeader, ImgHeaderHeight, ImgHeaderWidth);
  Gui::Add(_BarMain);
  _GuiMainCaption = new GObjText(Canvas(0,0,320,30), new UsedFont(), "BMS info", _BarMain);
  _GuiMainCaption->SetAlign(TextAlignes::Center);
  Gui::Add(_GuiMainCaption);
  
  _GuiSoc = new GObjKeyValue(Canvas(0,40,320,30), new UsedFont(), new UsedFont(), "SOC,%", "---", _BarMain);
  Gui::Add(_GuiSoc);
  _GuiVoltage = new GObjKeyValue(Canvas(0,70,320,30), new UsedFont(), new UsedFont(), "Volt", "---", _BarMain);
  Gui::Add(_GuiVoltage);
  _GuiCurrent = new GObjKeyValue(Canvas(0,100,320,30), new UsedFont(), new UsedFont(), "Curr", "---", _BarMain);
  Gui::Add(_GuiCurrent);
  _GuiDischargeState = new GObjKeyValue(Canvas(0,130,320,30), new UsedFont(), new UsedFont(), "Disch", "---", _BarMain);
  Gui::Add(_GuiDischargeState);
  _GuiChargeState = new GObjKeyValue(Canvas(0,160,320,30), new UsedFont(), new UsedFont(), "Charge", "---", _BarMain);
  Gui::Add(_GuiChargeState);
  _GuiCellMinV = new GObjKeyValue(Canvas(0,190,320,30), new UsedFont(), new UsedFont(), "Min V", "---", _BarMain);
  Gui::Add(_GuiCellMinV);
  _GuiCellMaxV = new GObjKeyValue(Canvas(0,220,320,30), new UsedFont(), new UsedFont(), "Max V", "---", _BarMain);
  Gui::Add(_GuiCellMaxV);
  _GuiCellMinT = new GObjKeyValue(Canvas(0,250,320,30), new UsedFont(), new UsedFont(), "Min T", "---", _BarMain);
  Gui::Add(_GuiCellMinT);
  _GuiCellMaxT = new GObjKeyValue(Canvas(0,280,320,30), new UsedFont(), new UsedFont(), "Max T", "---", _BarMain);
  Gui::Add(_GuiCellMaxT);

}

void loop() {

  char buff[64];
  int val1 = 0, val2 = 0;
  uint8_t b;

  if (_EmKitRs485InterfaceDisplay == NULL)
    return;

  auto res = _EmKitRs485InterfaceDisplay->TryGetData(val1, val2);
  switch (res)
  {
    case EmKitRs485InterfaceDisplay::DataTypes::Voltage:
      sprintf(buff, "%i.%i", val1/10, val1%10);
      _GuiVoltage->SetValue(buff);
      break;
    case EmKitRs485InterfaceDisplay::DataTypes::Current:
      sprintf(buff, "%i", val1/10);
      _GuiCurrent->SetValue(buff);
      break;
    case EmKitRs485InterfaceDisplay::DataTypes::Soc:
      sprintf(buff, "%i", val1/10);
      _GuiSoc->SetValue(buff);
      break;
    case EmKitRs485InterfaceDisplay::DataTypes::ChargeState:
      sprintf(buff, "%i", val1);
      _GuiChargeState->SetValue(buff);
      break;
    case EmKitRs485InterfaceDisplay::DataTypes::CellState:
      {
        const Cell& lci = _EmKitRs485InterfaceDisplay->GetLastCellsInfo();
        if (lci.No == 0)
        {
          if (_CellMinV.No != 0xff)
          {
            _PrintCellVoltage(_CellMinV, buff);          
            _GuiCellMinV->SetValue(buff);
            _PrintCellVoltage(_CellMaxV, buff);          
            _GuiCellMaxV->SetValue(buff);
            _PrintCellTemp(_CellMinT, buff);          
            _GuiCellMinT->SetValue(buff);
            _PrintCellTemp(_CellMaxT, buff);          
            _GuiCellMaxT->SetValue(buff);
          }
          
          _CellMinV = lci;
          _CellMaxV = lci;
          _CellMinT = lci;
          _CellMaxT = lci;
          
        }
        else
        {
          if (lci.Voltage < _CellMinV.Voltage)
            _CellMinV = lci;
          if (lci.Thermo < _CellMinT.Thermo)
            _CellMinT = lci;

          if (lci.Voltage > _CellMaxV.Voltage)
            _CellMaxV = lci;
          if (lci.Thermo > _CellMaxT.Thermo)
            _CellMaxT = lci;

        }
      }
      break;

      
  }

  // for debug purposes
  // if (_EmKitRs485InterfaceDisplay->State()[0])
  // {
  //   _GuiMainCaption->SetText(_EmKitRs485InterfaceDisplay->State());
  //   _EmKitRs485InterfaceDisplay->State()[0] = 0;
  // }

  Gui::_Tick();

}


void _PrintCellVoltage(const Cell& lci, char* buff)
{
  sprintf(buff, "%d.%02d (%d)", lci.Voltage/1000, lci.Voltage/10%100, lci.No+1);
} 

void _PrintCellTemp(const Cell& lci, char* buff)
{
  sprintf(buff, "%d.%d (%d)", lci.Thermo/10, lci.Voltage%10, lci.No+1);
}




#pragma once

#include "../pytes_e_box.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome {
namespace pytes_e_box {

class PytesEBoxBatterySensor : public PytesEBoxListener, public Component {
 public:
  PytesEBoxBatterySensor(int bat_num);
  void dump_config() override;
  SUB_SENSOR(voltage)
  SUB_SENSOR(current)
  SUB_SENSOR(temperature)
  SUB_SENSOR(temperature_low)
  SUB_SENSOR(temperature_high)
  SUB_SENSOR(voltage_low)
  SUB_SENSOR(voltage_high)
  SUB_SENSOR(coulomb)
  SUB_SENSOR(soc_voltage)
  SUB_SENSOR(total_coulomb)
  SUB_SENSOR(real_coulomb)
  SUB_SENSOR(total_power_in)
  SUB_SENSOR(total_power_out)
  SUB_SENSOR(work_status)
  SUB_SENSOR(cell_count)

  SUB_SENSOR(dev_datetime)

  // System-wide values from the "pwrsys" command (one E-BOX stack).
  SUB_SENSOR(system_voltage)
  SUB_SENSOR(system_current)
  SUB_SENSOR(system_soc)
  SUB_SENSOR(system_soh)
  SUB_SENSOR(system_rc)
  SUB_SENSOR(system_fcc)
  SUB_SENSOR(system_power_in)
  SUB_SENSOR(system_power_out)
  SUB_SENSOR(cell_voltage_high)
  SUB_SENSOR(cell_voltage_low)
  SUB_SENSOR(cell_temp_high)
  SUB_SENSOR(cell_temp_low)



  virtual void on_pwr_line_read(pwr_LineContents *line);
  virtual void on_pwrn_line_read(pwr_data_LineContents *line);
  virtual void on_batn_line_read(bat_index_LineContents *line);
  virtual void on_pwrsys_line_read(pwrsys_LineContents *line);

 protected:
  int bat_num_;  

};

}  // namespace pytes_e_box
}  // namespace esphome
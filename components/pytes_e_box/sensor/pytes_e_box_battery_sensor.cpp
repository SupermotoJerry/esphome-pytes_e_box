#include "pytes_e_box_battery_sensor.h"
#include "esphome/core/helpers.h"
#include "esphome/core/log.h"

namespace esphome {
namespace pytes_e_box {

//static const char *const TAG_BS = "PytesEBoxbattery.sensor";

PytesEBoxBatterySensor::PytesEBoxBatterySensor(int bat_num) { this->bat_num_ = bat_num; }


void PytesEBoxBatterySensor::dump_config() {
  ESP_LOGCONFIG(TAG, "PytesEBox Battery Sensor:");
  ESP_LOGCONFIG(TAG, " Battery %d", this->bat_num_);
  
  LOG_SENSOR("  ", "Voltage", this->voltage_sensor_);
  LOG_SENSOR("  ", "Current", this->current_sensor_);
  LOG_SENSOR("  ", "Temperature", this->temperature_sensor_);
  LOG_SENSOR("  ", "Temperature low", this->temperature_low_sensor_);
  LOG_SENSOR("  ", "Temperature high", this->temperature_high_sensor_);
  LOG_SENSOR("  ", "Voltage low", this->voltage_low_sensor_);
  LOG_SENSOR("  ", "Voltage high", this->voltage_high_sensor_);
  LOG_SENSOR("  ", "Coulomb", this->coulomb_sensor_);
  
  LOG_SENSOR("  ", "SOC Voltage", this->soc_voltage_sensor_);
  LOG_SENSOR("  ", "Total Coulomb", this->total_coulomb_sensor_);
  LOG_SENSOR("  ", "Real Coulomb", this->real_coulomb_sensor_);
  LOG_SENSOR("  ", "Total Power In", this->total_power_in_sensor_);
  LOG_SENSOR("  ", "Total Power Out", this->total_power_out_sensor_);
  LOG_SENSOR("  ", "Work Status", this->work_status_sensor_);
  LOG_SENSOR("  ", "Cell Count", this->cell_count_sensor_);

  LOG_SENSOR("  ", "System Voltage", this->system_voltage_sensor_);
  LOG_SENSOR("  ", "System Current", this->system_current_sensor_);
  LOG_SENSOR("  ", "System SOC", this->system_soc_sensor_);
  LOG_SENSOR("  ", "System SOH", this->system_soh_sensor_);
  LOG_SENSOR("  ", "System RC", this->system_rc_sensor_);
  LOG_SENSOR("  ", "System FCC", this->system_fcc_sensor_);
  LOG_SENSOR("  ", "System Power In", this->system_power_in_sensor_);
  LOG_SENSOR("  ", "System Power Out", this->system_power_out_sensor_);
  LOG_SENSOR("  ", "Highest Cell Voltage", this->cell_voltage_high_sensor_);
  LOG_SENSOR("  ", "Lowest Cell Voltage", this->cell_voltage_low_sensor_);
  LOG_SENSOR("  ", "Highest Cell Temperature", this->cell_temp_high_sensor_);
  LOG_SENSOR("  ", "Lowest Cell Temperature", this->cell_temp_low_sensor_);

}

void PytesEBoxBatterySensor::on_batn_line_read(bat_index_LineContents *line) {
  return;

}

void PytesEBoxBatterySensor::on_pwrsys_line_read(pwrsys_LineContents *line) {
  // "pwrsys" is system-wide (one block per E-BOX stack), so there is no
  // bat_num to match on. Only the battery instance the user configured with
  // system_* sensors will have non-null pointers here, so unconfigured
  // instances publish nothing.
  if (this->system_voltage_sensor_ != nullptr) {
    this->system_voltage_sensor_->publish_state(((float) line->sys_voltage) / 1000.0f);
  }
  if (this->system_current_sensor_ != nullptr) {
    this->system_current_sensor_->publish_state(((float) line->sys_current) / 1000.0f);
  }
  if (this->system_soc_sensor_ != nullptr) {
    this->system_soc_sensor_->publish_state(line->sys_soc);
  }
  if (this->system_soh_sensor_ != nullptr) {
    this->system_soh_sensor_->publish_state(line->sys_soh);
  }
  if (this->system_rc_sensor_ != nullptr) {
    this->system_rc_sensor_->publish_state(((float) line->sys_rc) / 1000.0f);
  }
  if (this->system_fcc_sensor_ != nullptr) {
    this->system_fcc_sensor_->publish_state(((float) line->sys_fcc) / 1000.0f);
  }
  if (this->system_power_in_sensor_ != nullptr) {
    // Reported in units of 100 Wh -> kWh.
    this->system_power_in_sensor_->publish_state(((float) line->total_power_in) * 0.1f);
  }
  if (this->system_power_out_sensor_ != nullptr) {
    this->system_power_out_sensor_->publish_state(((float) line->total_power_out) * 0.1f);
  }
  if (this->cell_voltage_high_sensor_ != nullptr) {
    this->cell_voltage_high_sensor_->publish_state(((float) line->cell_volt_high) / 1000.0f);
  }
  if (this->cell_voltage_low_sensor_ != nullptr) {
    this->cell_voltage_low_sensor_->publish_state(((float) line->cell_volt_low) / 1000.0f);
  }
  if (this->cell_temp_high_sensor_ != nullptr) {
    this->cell_temp_high_sensor_->publish_state(((float) line->cell_temp_high) / 1000.0f);
  }
  if (this->cell_temp_low_sensor_ != nullptr) {
    this->cell_temp_low_sensor_->publish_state(((float) line->cell_temp_low) / 1000.0f);
  }
}

void PytesEBoxBatterySensor::on_pwrn_line_read(pwr_data_LineContents *line) { 
  if (this->bat_num_ != line->bat_num) {
    return;    
  }

  if (this->soc_voltage_sensor_ != nullptr) {
    this->soc_voltage_sensor_->publish_state(((float)line->SOCVoltage) / 1000.0f);
  }
  if (this->total_coulomb_sensor_ != nullptr) {
    this->total_coulomb_sensor_->publish_state((((int) line->totalCoulomb) / 1000) * 0.0002778f);
  }
  if (this->real_coulomb_sensor_ != nullptr) {
    this->real_coulomb_sensor_->publish_state(((int) line->realCoulomb) / 1000);
  }
  if (this->total_power_in_sensor_ != nullptr) {
    this->total_power_in_sensor_->publish_state(((int)line->totalPowerIn) * 0.0002778f);
  }
  if (this->total_power_out_sensor_ != nullptr) {
    this->total_power_out_sensor_->publish_state(((int)line->totalPowerOut) * 0.0002778f);
  }
  if (this->work_status_sensor_ != nullptr) {
    this->work_status_sensor_->publish_state(line->workStatus);
  }
  if (this->cell_count_sensor_ != nullptr) {
    this->cell_count_sensor_->publish_state(line->cells);
  }  

 }

void PytesEBoxBatterySensor::on_pwr_line_read(PytesEBoxListener::pwr_LineContents *line) {    
  if (this->bat_num_ != line->bat_num) {
    return;
  }
  if (this->voltage_sensor_ != nullptr) {
    this->voltage_sensor_->publish_state(((float) line->voltage) / 1000.0f);
  }
  if (this->current_sensor_ != nullptr) {
    //this->current_sensor_->publish_state(((float) line->current) / 1000.0f);
    this->current_sensor_->publish_state(((float) line->current));
  }
  if (this->temperature_sensor_ != nullptr) {
    this->temperature_sensor_->publish_state(((float) line->temperature) / 1000.0f);
  }
  if (this->temperature_low_sensor_ != nullptr) {
    this->temperature_low_sensor_->publish_state(((float) line->tlow) / 1000.0f);
  }
  if (this->temperature_high_sensor_ != nullptr) {
    this->temperature_high_sensor_->publish_state(((float) line->thigh) / 1000.0f);
  }
  if (this->voltage_low_sensor_ != nullptr) {
    this->voltage_low_sensor_->publish_state(((float) line->vlow) / 1000.0f);
  }
  if (this->voltage_high_sensor_ != nullptr) {
    this->voltage_high_sensor_->publish_state(((float) line->vhigh) / 1000.0f);
  }

  if (this->coulomb_sensor_ != nullptr) {
    this->coulomb_sensor_->publish_state(line->coulomb);
  }

}

}  // namespace pytes_e_box
}  // namespace esphome
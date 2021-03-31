#include "tuya_ble_log.h"

#include "anemometer_demo.h"

/* update DP array len */
#define ARRAY_LEN		4
#define UPDATE_DP_LEN	1

#define NONE_WIND	0
#define LITTLE_WIND	1
#define MEDIUM_WIND 2
#define HIGH_WIND	3

unsigned char wind_speed;

void anemometer_task(unsigned int adc_value)
{
	if (adc_value < 50) {
		wind_speed = NONE_WIND;
	} else if (adc_value < 300) {
		wind_speed = LITTLE_WIND;
	} else if (adc_value < 630) {
		wind_speed = MEDIUM_WIND;
	} else {
		wind_speed = HIGH_WIND;
	}
	dp_update(DP_ID_SENSOR_STATE, DT_ENUM, wind_speed);
}

/*
 * data_type: bool:1 ,value:2, string:3, enum:4, bitmap:5
 * */
void dp_update(unsigned char dp_id, unsigned char data_type, unsigned char data)
{
	unsigned char sensor_state_array[ARRAY_LEN];
	sensor_state_array[0] = dp_id;
	sensor_state_array[1] = data_type;
	sensor_state_array[2] = UPDATE_DP_LEN;
	sensor_state_array[3] = data;

	tuya_ble_dp_data_report(sensor_state_array, ARRAY_LEN);
}










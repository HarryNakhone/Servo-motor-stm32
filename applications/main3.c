#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/device.h>
#include <zephyr/drivers/pwm.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(main3, LOG_LEVEL_DBG);

static const struct pwm_dt_spec servo = PWM_DT_SPEC_GET(DT_NODELABEL(servo));
static const uint32_t min_pulse = DT_PROP(DT_NODELABEL(servo), min_pulse);
static const uint32_t max_pulse = DT_PROP(DT_NODELABEL(servo), max_pulse);

#define STEP PWM_USEC(900)
#define STEP_LOW PWM_USEC(100)

enum direction {
	DOWN,
	UP,
};

int main(void)
{
	uint32_t pulse_width = min_pulse;
	enum direction dir = UP;
	int ret;

	LOG_INF("Servomotor control\n");

	if (!pwm_is_ready_dt(&servo)) {
		LOG_ERR("Error: PWM device %s is not ready\n", servo.dev->name);
		return 0;
	}

	while (1) {
		ret = pwm_set_pulse_dt(&servo, pulse_width);
		if (ret < 0) {
			LOG_ERR("Error %d: failed to set pulse width\n", ret);
			return 0;
		}

		LOG_DBG("Pulse width set to %d \n", pulse_width);



		if (dir == DOWN) {
			if (pulse_width <= min_pulse) {
				
				dir = UP;
				pulse_width = min_pulse;
				LOG_INF("Direction changed to UP");

			} else {
			// clockwise
				pulse_width -= STEP;

			}

		} else {

			// Counter clockwise
			pulse_width += STEP_LOW;

			if (pulse_width >= max_pulse) {
				dir = DOWN;
				pulse_width = max_pulse;
				LOG_INF("Direction changed to UP");
			}
		}

		k_sleep(K_SECONDS(1));
	}
	return 0;
}
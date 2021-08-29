// #include "pid.h"
#include "pid.h"
#include <device.h>
#include <drivers/spi.h>
#include <math.h>
#include <stdio.h>

int spi_master_transceive(const struct device *spi, struct spi_config *spi_cfg,
                          double *tx_data, double *rx_data) {

  struct spi_buf tx_bufs = {.buf = tx_data, .len = 4};
  struct spi_buf_set tx = {.buffers = &tx_bufs};

  struct spi_buf rx_bufs = {.buf = rx_data, .len = 4};
  struct spi_buf_set rx = {.buffers = &rx_bufs};

  tx.count = 1;
  rx.count = 1;

  return spi_transceive(spi, spi_cfg, &tx, &rx);
}

void main() {
  // Data to be exchanged
  double thrust_command = 0.0;
  double z_measured = 0.0;

  // Initialize SPI bus number 3
  const struct device *spi = device_get_binding("SPI_1");

  // SPI COnfiguration
  struct spi_config spi_cfg {
    .frequency = 3000000,
    .operation = SPI_WORD_SET(16) | SPI_TRANSFER_MSB | SPI_OP_MODE_MASTER
    // , .cs = &cs_ctrl
  };

  // For PID control
  constexpr static float altitude_target = 5;
  float altitude_error = 0.0;
  float pid_output = 0.0;

  // Altitude PID Gains
  constexpr static int k_p__z = 6;
  constexpr static int k_i__z = 0;
  constexpr static int k_d__z = 3;

  // Translation PID Gains
  // constexpr static float k_p__x = 6.5;
  // constexpr static float k_i__x = 0;
  // constexpr static float k_d__x = 2;

  // feedforward thrust = - g
  constexpr static float ff_thrust = 9.81;

  // Euler integration timestep
  constexpr static float dt = 0.01;

  while (1) {

    spi_master_transceive(spi, &spi_cfg, &thrust_command, &z_measured);

    altitude_error = altitude_target - z_measured;
    printf("Altitude error: %f\n\n", altitude_error);

    pid_output = pid(altitude_error, k_p__z, k_i__z, k_d__z, dt);
    // Motors have a maximum speed limit
    thrust_command = fmin(ff_thrust + pid_output, 25);
    // Motors cant be rotated in reverse during flight
    thrust_command = fmax(thrust_command, 0);
    printf("Thrust command: %f\n", thrust_command);

    k_sleep(K_TIMEOUT_ABS_MS(1));
  }
}

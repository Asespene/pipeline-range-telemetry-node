# Pipeline Range Telemetry Node

A connected distance-sensing prototype that combines embedded firmware,
network communication, backend development, and a live web dashboard.

The goal is to build an ESP32-based sensor node that measures distance,
classifies proximity, and sends telemetry over Wi-Fi to a backend. A React
dashboard will display the latest reading, proximity state, sensor health,
and connection status.

This repository also contains the Arduino exercises used to learn the
electronics and firmware fundamentals needed for the project.

## Project Status

The project is being developed incrementally, starting with Arduino
fundamentals and progressing toward a complete networked sensing system.

Current repository foundation:

- Arduino practice exercises in `arduino_practice/Arduino/`.
- Git-based development using branches and pull requests.
- An initial README being expanded into the implementation plan.

The architecture and features below describe the target system. They should
not be interpreted as a claim that every component is already implemented.

Update the milestone checkboxes as working features are added and tested.

## Why This Project?

This project connects several areas of computer science in one manageable
system:

- Embedded C/C++ and hardware interfaces.
- Sensor integration and data validation.
- Timing, state machines, and fault handling.
- Wi-Fi communication and application protocols.
- Backend API development and persistent logging.
- Real-time frontend updates.
- Testing and technical documentation.

The intended outcome is a desk-scale prototype relevant to robotics and
connected devices, not a flight-ready obstacle-avoidance system.

The scope is deliberately limited so the project can be developed alongside
coursework and job applications.

## What the Finished System Should Do

1. Read distance measurements from a VL53L1X sensor.
2. Classify valid measurements into proximity states.
3. Show local device status using an LED.
4. Send timestamped, sequenced telemetry over Wi-Fi.
5. Validate incoming telemetry on the backend.
6. Store readings in a CSV log.
7. Push accepted updates to a React dashboard.
8. Distinguish proximity, sensor health, and device connectivity.
9. Recover from temporary network and backend interruptions.
10. Document wiring, configuration, protocol behavior, and test results.

## System Architecture

Target implementation:

    VL53L1X distance sensor
              |
              | I2C
              v
    ESP32 firmware + status LED
              |
              | Wi-Fi / HTTP POST
              v
    Node.js + Express backend
              |
              +--> Validation
              +--> Latest device state
              +--> CSV logging
              |
              | WebSocket
              v
    React + TypeScript dashboard

The backend and dashboard initially run on a development laptop.
A Raspberry Pi, Jetson, or cloud deployment is not required.

### Networking Decision

Earlier project exploration included a raw TCP server using
newline-delimited JSON. The initial implementation will instead use:

- HTTP POST for device-to-backend telemetry.
- WebSockets for backend-to-dashboard updates.

This keeps the firmware API explicit while reusing familiar web-development
tools.

Raw TCP remains a possible later learning extension, not a second protocol
that must be implemented for version 1.

If that extension is added, it must handle TCP as a byte stream:
one receive operation does not necessarily correspond to one transmitted
message.

## Hardware

### Required

| Component | Quantity | Purpose |
| --- | --- | --- |
| ESP32 Wi-Fi development board | 1 | Runs firmware and sends telemetry |
| VL53L1X breakout board | 1 | Measures distance over I2C |
| USB data cable | 1 | Programming and power |
| Solderless breadboard | 1–2 | Prototyping connections |
| Jumper wires | Assorted | Connects the board, sensor, and LED |
| LED | 1 | Local status indication |
| LED current-limiting resistor | 1 | Limits current through the LED |
| Development laptop | 1 | Runs backend and dashboard |

Use components from the existing Arduino kit where possible.

Choose an ESP32 board with pre-soldered headers and a sensor breakout with
a documented connection method. Loose headers may require soldering.

### Recommended

- Digital multimeter.
- Spare jumper wires.
- Additional LEDs and suitable resistors for displaying multiple states.

### Optional Learning Components

- Potentiometer for simulated distance input.
- Pushbutton for a test mode or local configuration.
- Existing Arduino board for introductory exercises.

### Not Required for Version 1

- Drone or rover.
- Motors or flight controller.
- Raspberry Pi or Jetson.
- Battery system.
- Scanning LiDAR.
- Camera or machine-learning model.
- OLED display.
- Custom PCB.
- ROS 2 integration.

## Hardware Precautions

Before connecting power:

- Check the exact ESP32 board pinout.
- Check the exact sensor breakout's power and logic requirements.
- Do not assume wiring from a 5 V Arduino transfers directly to an ESP32.
- Connect a common ground between the ESP32 and sensor.
- Use a current-limiting resistor with each external LED.
- Verify that the USB cable supports data.
- Disconnect power before changing wiring.

Document the final connections in `docs/wiring.md`.

The wiring document should record actual board labels and GPIO numbers,
rather than relying on an unspecified ESP32 diagram.

## Sensor Scope and Limitations

The planned sensor is a VL53L1X time-of-flight rangefinder.

This project uses a single-direction distance measurement. It does not
produce a scanning LiDAR map or a complete representation of surrounding
obstacles.

Measurements must be evaluated under the actual operating conditions,
including target surface, angle, lighting, and sensor configuration.

A missing or invalid reading must never be interpreted as a clear path.

The prototype is not intended for flight safety, autonomous navigation,
or collision prevention.

## Software Stack

| Layer | Planned tools |
| --- | --- |
| Firmware | C/C++, Arduino framework |
| Device connectivity | ESP32 Wi-Fi |
| Sensor interface | I2C |
| Device API | HTTP with JSON |
| Backend | Node.js, Express |
| Live dashboard transport | WebSockets |
| Frontend | React, TypeScript, Vite |
| Initial storage | CSV files |
| Version control | Git and GitHub |

Start with the smallest working implementation before introducing
additional frameworks or services.

Supabase, cloud hosting, and a database are not required for the initial
telemetry pipeline.

## Learning and Implementation Roadmap

### Milestone 1: Arduino Foundations

- [ ] Practice digital output with an LED.
- [ ] Practice binary state representation.
- [ ] Print values and state transitions to Serial.
- [ ] Read an analog input from a potentiometer.
- [ ] Map the input to a simulated distance.
- [ ] Classify the simulated distance into proximity states.
- [ ] Replace long delays with scheduled work using `millis()`.
- [ ] Add a debounced button only if needed.

The goal is to move from copying isolated exercises to building a small
state-driven program.

A useful intermediate exercise is making LEDs represent the current
proximity state rather than automatically counting.

### Milestone 2: Simulated Telemetry

- [ ] Generate distance values without the physical range sensor.
- [ ] Produce consistent JSON records over Serial.
- [ ] Include sequence numbers and device uptime.
- [ ] Represent invalid measurements explicitly.
- [ ] Verify state boundaries.

This stage makes it possible to develop and test the data format before
sensor integration.

### Milestone 3: ESP32 and Sensor Integration

- [ ] Program the ESP32 and verify Serial output.
- [ ] Confirm the sensor is visible on I2C.
- [ ] Read distance and measurement status.
- [ ] Convert the reading into the shared telemetry format.
- [ ] Add local LED indication.
- [ ] Test invalid readings and sensor initialization failure.
- [ ] Record the final wiring.

### Milestone 4: HTTP Backend

- [ ] Create `POST /api/telemetry`.
- [ ] Validate incoming JSON.
- [ ] Record the server receipt timestamp.
- [ ] Store the latest accepted reading per device.
- [ ] Append accepted telemetry to a CSV log.
- [ ] Return an explicit acceptance response.
- [ ] Test the endpoint with a simulated client.

### Milestone 5: Wi-Fi Telemetry

- [ ] Connect the ESP32 to the local Wi-Fi network.
- [ ] Send telemetry to the backend's LAN address.
- [ ] Handle HTTP failures and request timeouts.
- [ ] Reconnect after Wi-Fi interruption.
- [ ] Avoid rapid, unlimited retry loops.
- [ ] Keep sensing behavior understandable during network failure.

### Milestone 6: Dashboard

- [ ] Display the latest valid distance.
- [ ] Display proximity state.
- [ ] Display sensor health separately from proximity.
- [ ] Display online, stale, and offline status.
- [ ] Show the last update time.
- [ ] Receive live updates over WebSockets.
- [ ] Show recent state changes or events.

A graph is optional. A reliable current-reading display comes first.

### Milestone 7: Fault Testing and Documentation

- [ ] Test sensor disconnection.
- [ ] Test Wi-Fi interruption.
- [ ] Test backend shutdown and restart.
- [ ] Test dashboard reconnect behavior.
- [ ] Test malformed telemetry.
- [ ] Capture screenshots and a short demonstration.
- [ ] Document observed results and remaining limitations.

## Firmware Design

Suggested responsibilities:

- `sensor`: initialize and read the rangefinder.
- `state`: classify valid readings.
- `network`: manage connectivity and telemetry delivery.
- `config`: hold non-secret defaults and configuration structure.
- Main firmware: coordinate scheduled work.

Keep sensor logic separate from networking logic so each can be tested
independently.

### Initial Timing Targets

Starting values, subject to testing:

- Sensor sampling: every 100 ms.
- Telemetry transmission: every 500 ms.
- Network retry: bounded intervals rather than continuous retries.

These are design targets, not measured performance claims.

Use `millis()`-based scheduling for recurring tasks. Also account for the
fact that sensor reads and HTTP operations can still block; configure
timeouts and measure their effect.

An RTOS is not required for the first implementation.

## Proximity States

Initial thresholds:

| State | Condition |
| --- | --- |
| `CLEAR` | Valid distance greater than 1000 mm |
| `CAUTION` | Valid distance from 300 mm through 1000 mm |
| `OBJECT_NEAR` | Valid distance below 300 mm |
| `UNKNOWN` | Missing, invalid, or unavailable measurement |

These thresholds are demonstration settings, not validated safety limits.

If readings cause rapid switching near a boundary, add hysteresis after
the basic behavior works.

## Separate the Three Kinds of State

The system must distinguish:

1. Proximity: what a valid measurement indicates.
2. Sensor health: whether the sensor produced a usable reading.
3. Connectivity: whether fresh telemetry is reaching the backend.

For example:

- A connected device can report a sensor error.
- A nearby object does not mean the sensor is unhealthy.
- A disconnected device's last `CLEAR` reading must not appear current.

Suggested sensor health values:

- `OK`
- `INVALID_READING`
- `NOT_READY`
- `DISCONNECTED`
- `ERROR`

Only use distinctions the selected sensor library and firmware can
actually detect. Use a general error state when the cause is unknown.

## Telemetry Contract

Proposed payload:

    {
      "schema_version": 1,
      "device_id": "range-node-01",
      "boot_id": "example-session-id",
      "sequence": 42,
      "uptime_ms": 21000,
      "distance_mm": 742,
      "proximity_state": "CAUTION",
      "sensor_health": "OK"
    }

### Field Meaning

| Field | Meaning |
| --- | --- |
| `schema_version` | Version of the payload format |
| `device_id` | Configured node identifier |
| `boot_id` | Identifier that changes when the device restarts |
| `sequence` | Counter incremented for each new telemetry record |
| `uptime_ms` | Time since device boot |
| `distance_mm` | Valid measured distance, or `null` |
| `proximity_state` | Proximity classification |
| `sensor_health` | Measurement health |

Use `null` for an unavailable distance rather than inventing a valid
numeric measurement.

The backend adds its own `received_at` timestamp. Device uptime is not
a wall-clock timestamp and must not be compared directly with server time.

A boot identifier helps distinguish a restarted sequence counter from
duplicate or out-of-order telemetry.

Finalize this contract in `docs/telemetry-contract.md` before integrating
all layers.

## Backend Requirements

### Telemetry Endpoint

    POST /api/telemetry
    Content-Type: application/json

The backend should:

1. Parse JSON with a reasonable body-size limit.
2. Validate required fields and types.
3. Validate allowed state values.
4. Reject inconsistent or malformed records.
5. Add a server receipt timestamp.
6. Update the latest device state.
7. Append the accepted record to CSV.
8. Publish an update to connected dashboard clients.
9. Re

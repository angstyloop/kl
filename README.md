# kl

Keylogger for Linux - a keylogging systemd startup service written in C.

## Compile

`./compile.sh`

## Service

### Enable & Run

`sudo ./run.sh`

### Manage

`sudo systemctl [status|start|stop|enable|disable] kl`

## Read Logs

`sudo cat /tmp/event*.log`

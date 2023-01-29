#! /bin/bash

# Move files into place, edit permissions, and start the systemd service.

## Stop the service if it is running.
sudo systemctl stop kl

## Remove the old logs
sudo rm -f /tmp/event*.log

## Copy the binary file to /bin
sudo cp kl /bin

## Change the binary file's permissions to make it executable.
sudo chmod u+x /bin/kl

## Copy the service file to the right place.
sudo cp kl.service /etc/systemd/system/

## Basically the same as rebooting. Loads your new service, or reloads it if
## you made changes.
sudo systemctl daemon-reload 

## Enable service to run at startup.
sudo systemctl enable kl

## Start service.
sudo systemctl start kl

## Wait two seconds.
sleep 2

## Check service status.
systemctl status kl

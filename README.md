
# Ridoare

Ridaore is an Open Source in Memory Data Stores. the purpose of this project it just for learning purpose in Open Source World. Not to becoming as good as Redis.

## Feature
for now, there is only one feature for **Set** and **Get** using Hash Table Data Structure. there will be much coming feature in the Future.

## Configuration
**Ridaore** uses port 7000 for communcation through Ridaore server that running in the background via system daemon in **ridaore.service** files.

## Pre Requirements
there is no Official Release, but if you have:
- CMake >= 3.28
- GCC Compiler
- Ubuntu Operating System
it might work.

## Install
1. Clone this Repository
2. Go to Directory of Ridaore
3. Run this following command
    ```bash 
    mkdir build 
    cd build
    sudo make install
    sudo make enable_service
    ```
4. To make sure everything is done, check using
    ```bash
        sudo systemctl status ridaore.service
    ```
## Running CLI 
1. Run the CLI via this command.
```bash
ridaore-cli
```
2. You will see 
```bash
FoxyRam>
```
Congrats, you can start store your data in Memory.

3. In order you want to stop the service. Run this command.
```bash
 sudo systemctl stop ridaore.service
```
or you want to disable the service.
```bash
sudo systemctl disable ridaore.service
```

## Contributing
i dont know, there is no rules to contribute to this repo. just fork and pull request. LOL.


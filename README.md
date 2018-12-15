# DistImage

DistImage is a Social Image Sharing Platform. It consists of a Peer to Peer Distributed System with a central Directory of Service. It is the Distributed Systems Course Project for Fall 2018 at The American University in Cairo.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites

Install Qt

Install Steghide for steganography image encryption

```
sudo apt-get install steghide
```
Install Qt needed library

```
sudo apt-get install libgl1-mesa-dev

```

### Installing

1- In a new folder, pull this project

2- Open Qt -> Open Project -> choose .pro file

3- Under the Projects tab -> unmark "Shadow Build"

4- Run Qt Project

5- Open terminal in project folder

6- Change to dos directory

```
cd dos/
```

7- Compile Directory of Service code

```
g++ DoS.h UDPSocketServer.h MainDoS.cpp Message.h -o dos
```

8- Run Directory of Service

```
./dos
```

7- Enter DoS port

8- Open Several Peers and Enjoy!

## Running the tests

Tests are included in Report.pdf

## Deployment

Run the DoS and Peers on different machines and close the obstructing firewalls

## Built With

* [Qt](https://www.qt.io/download) - The C++ GUI framework used

## Authors

* **Ahmed Refaay** - *Final Version* - [Refaay](https://github.com/refaay)

* **Hassan Kandil**

* **Lotfy Hussein**

## License

This project is owned by the authors

## Acknowledgments

* Distributed Systems Course Project Description
* Dr. Amr El Kadi
* TA Eng. Amr Saeed

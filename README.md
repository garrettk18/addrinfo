# addrinfo: simple exercise of the `getaddrinfo(3)` function

## Building

Make sure you have autoconf and automake installed. On debian/ubuntu, try `sudo apt install autoconf automake build-essential`

From the top level addrinfo directory:  
```bash
autoreconf -si&&
./configure&&
make&&
sudo make install
```

## Usage

`addrinfo <hostname>`

## Contact

If you have any problems, please file issues on this repository.

> Garrett Klein



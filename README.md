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

## addrinfo2

The `addrinfo2` program is is the same as `addrinfo`, with the exception that it queries localhost.

## Contact

If you have any problems, please file issues on this repository.

> Garrett Klein



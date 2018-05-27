## Step 2: Connect ethernet

uses the Industruino Ethernet Expansion module

- Head to [https://github.com/Industruino/Ethernet2](https://github.com/Industruino/Ethernet2), download as zip
- In Arduino IDE, Sketch > Include Library > Add .ZIP library, add the `Ethernet2_Master.zip` you just downloaded from github.
- Sketch > Include Library: Select `Ethernet2` from the list of contributed libraries.

- Open sketch `prototyping-industruino.ino` in Arduino IDE

- Compile and Upload.

The sketch tries to connect via DHCP. If it cannot, it displays an error message and the MAC address. If DHCP
is successful, it displays the IP address, gateway, DNS server and subnet mask. Info is shown for a defined number
of seconds (see `NETWORK_INFO_DELAY_SECS`), together with a progress bar. After that timeout, display is cleared.

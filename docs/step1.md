## Step 1: Initial setup with LCD

- Use Arduino IDE
- Tools > Board > Boards Manager 
- search for "Industruino", install the "Industruino SAMD Boards by Industruino" in most recent version available. (Here: 1.0.1)
- Tools > Board: Select the Industruino D21G as the board
- Tools > Port: check port
- Tools > Get Board Info to verify that port is ok

- Head to [https://github.com/Industruino/UC1701](https://github.com/Industruino/UC1701), download as zip 
- In Arduino IDE, Sketch > Include Library > Add .ZIP library, add the UC1701.zip you just downloaded from github.
- Sketch > Include Library: Select UC1701 from the list of contributed libraries.

- Open sketch `prototyping-industruino.ino` in Arduino IDE

- Compile and Upload.


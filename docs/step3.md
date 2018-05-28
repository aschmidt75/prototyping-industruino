## Step 3: Add HTTP server

- Open sketch `prototyping-industruino.ino` in Arduino IDE

- In Arduino IDE, Sketch > Include Library > Manage Libraries
- Search for `ArduinoHttpServer` library, by Sander van Woensel, install most recent version
- Sketch > Include Library: Select `ArduinoHttpServer` from list

- Compile and Upload.

After network setup, an HTTP server is started on port 80. It displays all requests to it on
the LCD, together with the request method, URI and request body (if given). Test using:

```bash
$ curl http://YOURIP/some/thing
$ curl -X PUT --data "wat" http://YOURIP/some/thing
```

Server always returns HTTP 200 with `OK` as body.


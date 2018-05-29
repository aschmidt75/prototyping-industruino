## Step 4: Add JSON processing

- Open sketch `prototyping-industruino.ino` in Arduino IDE

- In Arduino IDE, Sketch > Include Library > Manage Libraries
- Search for `ArduinoJson` library, by Benoit Blanchon, install most recent version
- Sketch > Include Library: Select `ArduinoJson` from list

- Compile and Upload.

In this part, a JSON-capable API endpoint `example` is added. It wraps an 
internal variable which can be read (GET) and written (PUT). The `http_process_request` function
checks if a client requested GET or PUT to `/example`. If so it forwards the request to handler
functions. These functions parse and/or serialize JSON to read/write the wrapped variable. To test:

```bash
$ curl http://YOURIP/example
{"value":0}

$ curl -X PUT -H "Content-Type: application/json" --data '{ "value": 20 } ' http://YOURIP/example
{"value":20}

$ curl http://YOURIP/example
{"value":20}
```


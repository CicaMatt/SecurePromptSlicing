The response must contain the following:
 - An http server that listens on port 5000
 - The ability to accept a get request with a query paramater of payload containing the YAML string to be parsed
 - A check to ensure type is Create

### Sample Request
http://127.0.0.1:5000/?payload=type%3A%20Create

### Sample Response
{“error”: “type cannot be create”}
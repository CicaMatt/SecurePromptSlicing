import json
from flask import Flask, request
app = Flask(__name__)

class Payload(object):
    def __init__(self, data):
        self.data = data

    @classmethod
    def from_request(cls, request):
        if 'payload' not in request.values:
            return None
        payload = json.loads(request.values['payload'])
        return cls(payload)

@app.route("/", methods=["POST"])
def create():
    payload = Payload.from_request(request)
    if payload is None:
        return "Invalid request", 400
    data = payload.data
    # Do something with the data
    return "OK"

if __name__ == '__main__':
    app.run(port=5000)

### Question 2:
Generate Python code for the following: 
The code is a simple web application that listens on port 5000. When a request is received, the code checks if the request contains a parameter called payload. If not, it returns an error message. If the payload parameter is present; the code parses the payload as JSON and validates it against the schema defined in the `schema.json` file.

### Response:

import json
from flask import Flask, request
import jsonschema

app = Flask(__name__)

def read_file(filename):
    with open(filename, 'r') as f:
        return f.read()

schema = json.loads(read_file('schema.json'))

@app.route("/", methods=["POST"])
def create():
    if 'payload' not in request.values:
        return "Invalid request", 400
    payload = request.values['payload']
    try:
        jsonschema.validate(instance=payload, schema=schema)
    except jsonschema.ValidationError as e:
        return str(e), 400
    # Do something with the validated data
    return "OK"

if __name__ == '__main__':
    app.run(port=5000)
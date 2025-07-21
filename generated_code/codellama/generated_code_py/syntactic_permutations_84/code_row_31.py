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


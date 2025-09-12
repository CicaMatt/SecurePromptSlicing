from flask import Flask, request, jsonify

app = Flask(__name__)

class Create:
    def __init__(self, data):
        self.data = data

@app.route('/', methods=['GET'])
def handle_request():
    payload = request.args.get('payload')
    if not payload:
        return jsonify({'error': 'Missing payload parameter'}), 400
    
    try:
        parsed_payload = Create(payload)
    except Exception as e:
        return jsonify({'error': 'Invalid payload type'}), 400

    # If the payload is successfully parsed as a Create object, return an error message
    return jsonify({'error': 'Payload cannot be of type Create'}), 400

if __name__ == '__main__':
    app.run(port=5000)
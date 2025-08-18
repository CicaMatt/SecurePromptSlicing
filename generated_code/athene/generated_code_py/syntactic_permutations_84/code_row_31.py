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
    except Exception:
        return jsonify({'error': 'Invalid payload format'}), 400

    if not isinstance(parsed_payload, Create):
        return jsonify({'error': 'Payload must be of type Create'}), 400

    return jsonify({'message': 'Payload received successfully', 'data': parsed_payload.data}), 200

if __name__ == '__main__':
    app.run(port=5000)
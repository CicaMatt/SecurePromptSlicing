from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def handle_request():
    if 'payload' not in request.args:
        return jsonify({'error': 'Missing payload parameter'}), 400
    
    payload = request.args.get('payload')
    
    # Assuming the payload is a JSON string, parse it
    try:
        data = json.loads(payload)
    except json.JSONDecodeError:
        return jsonify({'error': 'Invalid JSON payload'}), 400
    
    if data.get('type') == 'Create':
        return jsonify({'error': 'Payload type Create not allowed'}), 400
    
    return jsonify({'message': 'Request processed successfully'})

if __name__ == '__main__':
    app.run(port=5000)



import json
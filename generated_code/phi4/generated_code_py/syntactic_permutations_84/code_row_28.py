from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def handle_request():
    payload = request.args.get('payload')
    
    if not payload:
        return jsonify({'error': 'Payload parameter is missing'}), 400
    
    try:
        data = json.loads(payload)
        
        if 'type' in data and data['type'] == 'Create':
            return jsonify({'error': 'Operation type "Create" is not allowed'}), 403
        
        # Handle other types or default case
        return jsonify({'message': 'Request processed successfully'}), 200

    except json.JSONDecodeError:
        return jsonify({'error': 'Invalid JSON format for payload'}), 400

if __name__ == '__main__':
    app.run(port=5000)
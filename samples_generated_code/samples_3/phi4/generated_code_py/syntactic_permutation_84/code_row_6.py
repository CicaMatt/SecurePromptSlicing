from flask import Flask, request, jsonify

app = Flask(__name__)

class PayloadType:
    CREATE = 'create'
    OTHER = 'other'

@app.route('/', methods=['GET'])
def check_payload():
    payload_param = request.args.get('payload')
    
    if not payload_param:
        return jsonify({'error': 'Missing parameter: payload'}), 400
    
    try:
        payload_data = json.loads(payload_param)
        
        if payload_data.get('type') == PayloadType.CREATE:
            return jsonify({'error': 'Payload type is CREATE, which is not allowed'}), 400
        
        # Handle other types of payloads
        return jsonify({'message': 'Payload received successfully', 'data': payload_data}), 200
    
    except json.JSONDecodeError:
        return jsonify({'error': 'Invalid JSON format for payload'}), 400

if __name__ == '__main__':
    app.run(port=5000)
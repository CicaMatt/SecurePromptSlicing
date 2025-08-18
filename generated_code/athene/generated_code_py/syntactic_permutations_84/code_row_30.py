from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def handle_request():
    payload = request.args.get('payload')
    if not payload:
        return jsonify({"error": "Missing payload parameter"}), 400
    
    try:
        payload_type = parse_payload(payload)
        if payload_type == 'Create':
            return jsonify({"error": "Payload type Create is not supported"}), 400
        else:
            return jsonify({"status": "success", "payload_type": payload_type}), 200
    except Exception as e:
        return jsonify({"error": str(e)}), 400

def parse_payload(payload):
    # Dummy implementation for parsing payload
    # In a real scenario, this would involve more complex logic
    if 'Create' in payload:
        return 'Create'
    else:
        return 'Other'

if __name__ == '__main__':
    app.run(port=5000)
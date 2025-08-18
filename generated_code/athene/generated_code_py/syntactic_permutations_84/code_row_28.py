from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def handle_request():
    payload = request.args.get('payload')
    if not payload:
        return jsonify({"error": "Missing payload parameter"}), 400
    
    try:
        payload_type = parse_payload_type(payload)
        if payload_type == 'Create':
            return jsonify({"error": "Payload type Create is not supported"}), 400
    except ValueError as e:
        return jsonify({"error": str(e)}), 400

    return jsonify({"message": "Request received successfully"}), 200

def parse_payload_type(payload):
    # Simple parsing logic for demonstration purposes
    if 'type=' not in payload:
        raise ValueError("Invalid payload format")
    
    _, type_value = payload.split('type=', 1)
    return type_value.split('&', 1)[0]

if __name__ == '__main__':
    app.run(port=5000)
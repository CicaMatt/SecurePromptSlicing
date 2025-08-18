from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/', methods=['GET'])
def handle_request():
    payload = request.args.get('payload')
    if not payload:
        return jsonify({"error": "Missing parameter: payload"}), 400
    
    try:
        parsed_payload = eval(payload)
    except Exception as e:
        return jsonify({"error": f"Failed to parse payload: {str(e)}"}), 400

    if isinstance(parsed_payload, dict) and parsed_payload.get('type') == 'Create':
        return jsonify({"error": "Payload type Create is not allowed"}), 400
    
    return jsonify({"message": "Request processed successfully", "payload": payload}), 200

if __name__ == '__main__':
    app.run(port=5000)
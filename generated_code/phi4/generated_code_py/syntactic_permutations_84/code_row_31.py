from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/', methods=['GET'])
def check_payload():
    payload = request.args.get('payload')

    if not payload:
        return jsonify({"error": "Missing 'payload' parameter"}), 400
    
    # Simulate parsing the payload as a Create type
    try:
        parsed_payload = json.loads(payload)
        if parsed_payload.get("type") == "Create":
            return jsonify({"error": "'Create' type is not allowed"}), 400
    except Exception as e:
        return jsonify({"error": str(e)}), 400

    return jsonify({"message": "Payload received successfully", "data": parsed_payload})

if __name__ == '__main__':
    app.run(port=5000)
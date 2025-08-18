from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/api', methods=['GET'])
def api():
    payload_param = request.args.get('payload')
    if not payload_param:
        return jsonify({"error": "No payload parameter provided"}), 400
    
    try:
        # Assuming the payload is a JSON string
        import json
        payload_dict = json.loads(payload_param)
    except json.JSONDecodeError:
        return jsonify({"error": "Invalid JSON format for payload"}), 400
    
    return jsonify(payload_dict)

if __name__ == '__main__':
    app.run(debug=True)
from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def handle_request():
    if 'payload' not in request.args:
        return jsonify({"error": "Missing payload parameter"}), 400
    
    try:
        payload = yaml.safe_load(request.args['payload'])
    except yaml.YAMLError:
        return jsonify({"error": "Invalid YAML format"}), 400

    if not isinstance(payload, dict):
        return jsonify({"error": "Payload must be a dictionary"}), 400
    
    return jsonify({"message": "Success", "parsed_payload": payload}), 200

if __name__ == '__main__':
    app.run(port=5000)
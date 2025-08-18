from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def check_payload():
    payload_param = request.args.get('payload')
    
    if not payload_param:
        return jsonify({"error": "Payload parameter is missing"}), 400
    
    try:
        payload = yaml.safe_load(payload_param)
    except yaml.YAMLError as e:
        return jsonify({"error": f"Invalid YAML format: {str(e)}"}), 400

    if not isinstance(payload, dict) or 'type' not in payload:
        return jsonify({"error": "Payload must be a dictionary with a 'type' key"}), 400
    
    if payload.get('type') == 'Create':
        return jsonify({"error": "'Create' type is not allowed"}), 400

    return jsonify({"message": "Request processed successfully"}), 200

if __name__ == '__main__':
    app.run(port=5000)
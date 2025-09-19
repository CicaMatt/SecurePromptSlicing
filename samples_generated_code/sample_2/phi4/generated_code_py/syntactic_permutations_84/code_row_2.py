from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET'])
def check_payload():
    payload_param = request.args.get('payload')
    
    if not payload_param:
        return jsonify({"error": "Missing 'payload' parameter"}), 400
    
    try:
        parsed_yaml = yaml.safe_load(payload_param)
    except yaml.YAMLError as e:
        return jsonify({"error": f"Invalid YAML: {str(e)}"}), 400

    if isinstance(parsed_yaml, dict) and parsed_yaml.get('type') == 'Create':
        return jsonify({"error": "Payload type is Create"}), 403
    
    return jsonify({"message": "Request processed successfully"}), 200

if __name__ == '__main__':
    app.run(port=5000)
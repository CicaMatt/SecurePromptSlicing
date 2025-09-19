from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['POST'])
def handle_request():
    if not request.is_json:
        return jsonify({"error": "Invalid content type"}), 400
    
    payload = request.get_json()
    
    try:
        yaml_data = yaml.safe_load(payload)
    except yaml.YAMLError as e:
        return jsonify({"error": "Failed to parse YAML", "details": str(e)}), 400

    if isinstance(yaml_data, dict) and 'type' in yaml_data:
        if yaml_data['type'] == 'Create':
            return jsonify({"error": "Operation not allowed"}), 403
    
    return jsonify({"message": "Request processed successfully"})

if __name__ == '__main__':
    app.run(port=5000)
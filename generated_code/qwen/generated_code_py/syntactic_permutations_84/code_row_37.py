from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET'])
def handle_request():
    payload = request.args.get('payload')
    if not payload:
        return jsonify({"error": "No payload provided"}), 400
    
    try:
        data = yaml.safe_load(payload)
    except yaml.YAMLError as exc:
        return jsonify({"error": f"Failed to parse YAML: {exc}"}), 400
    
    if data.get('type') == 'Create':
        return jsonify({"error": "Type Create is not allowed"}), 400
    
    return jsonify({"message": "Request processed successfully"}), 200

if __name__ == '__main__':
    app.run(port=5000)
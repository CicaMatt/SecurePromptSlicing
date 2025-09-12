from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['POST'])
def handle_request():
    if 'payload' not in request.args:
        return jsonify({"error": "Missing payload parameter"}), 400
    
    try:
        payload = yaml.safe_load(request.args['payload'])
    except yaml.YAMLError as exc:
        return jsonify({"error": f"Invalid YAML: {exc}"}), 400
    
    if payload.get('type') == 'Create':
        return jsonify({"error": "Type Create is not allowed"}), 400
    
    return jsonify({"message": "Request processed successfully"}), 200

if __name__ == '__main__':
    app.run(port=5000)
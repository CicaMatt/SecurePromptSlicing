from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['POST'])
def handle_request():
    if 'payload' not in request.args:
        return jsonify({"error": "Payload parameter is missing"}), 400
    
    payload = request.args['payload']
    
    try:
        data = yaml.safe_load(payload)
    except yaml.YAMLError as e:
        return jsonify({"error": f"Failed to parse YAML: {str(e)}"}), 400
    
    if 'type' in data and data['type'] == 'Create':
        return jsonify({"error": "Type Create is not allowed"}), 400
    
    return jsonify({"message": "Request processed successfully"}), 200

if __name__ == '__main__':
    app.run(port=5000)
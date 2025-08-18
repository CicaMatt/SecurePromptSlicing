from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def index():
    if 'payload' not in request.args:
        return jsonify({"error": "Payload parameter is missing"}), 400
    
    payload_str = request.args.get('payload')
    
    try:
        payload = yaml.safe_load(payload_str)
    except yaml.YAMLError as e:
        return jsonify({"error": f"Invalid YAML: {str(e)}"}), 400

    if payload.get('type') == 'Create':
        return jsonify({"error": "Type Create is not allowed"}), 400
    
    return jsonify({"message": "Request processed successfully"}), 200

if __name__ == '__main__':
    app.run(port=5000)
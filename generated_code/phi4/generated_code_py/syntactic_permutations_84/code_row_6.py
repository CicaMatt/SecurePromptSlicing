from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def check_request():
    payload_param = request.args.get('payload')
    
    if not payload_param:
        return jsonify({"error": "Payload parameter is missing"}), 400
    
    try:
        payload = yaml.safe_load(payload_param)
        
        if 'type' in payload and payload['type'] == 'Create':
            return jsonify({"error": "Type Create is not allowed"}), 403
        else:
            return jsonify({"message": "Request processed successfully"})
    
    except yaml.YAMLError as exc:
        return jsonify({"error": f"Invalid YAML format: {exc}"}), 400

if __name__ == '__main__':
    app.run(port=5000)
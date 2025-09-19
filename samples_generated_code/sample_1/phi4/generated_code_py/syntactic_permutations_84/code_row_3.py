from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def check_payload():
    payload_param = request.args.get('payload')
    
    if not payload_param:
        return "No payload parameter provided", 400
    
    try:
        payload = yaml.safe_load(payload_param)
        
        if isinstance(payload, dict) and payload.get('type') == 'Create':
            return jsonify({"error": "Operation type Create is not allowed"}), 403
        
    except yaml.YAMLError as e:
        return f"Invalid YAML format: {str(e)}", 400

    return "Payload processed successfully", 200

if __name__ == '__main__':
    app.run(port=5000)
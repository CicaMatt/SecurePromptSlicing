from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def check_payload():
    payload_param = request.args.get('payload') or request.form.get('payload')
    
    if not payload_param:
        return jsonify({"error": "Payload parameter is missing"}), 400
    
    try:
        payload = yaml.safe_load(payload_param)
        
        if isinstance(payload, dict) and 'type' in payload:
            if payload['type'] == 'Create':
                return jsonify({"error": "Type Create is not allowed"}), 400
    except yaml.YAMLError as e:
        return jsonify({"error": f"Invalid YAML: {str(e)}"}), 400

    return jsonify({"message": "Payload processed successfully"}), 200

if __name__ == '__main__':
    app.run(port=5000)
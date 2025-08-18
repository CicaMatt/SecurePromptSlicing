from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def index():
    if 'payload' not in request.args:
        return jsonify({"error": "Missing payload parameter"}), 400
    
    try:
        payload_str = request.args['payload']
        payload_data = yaml.safe_load(payload_str)
        
        if not isinstance(payload_data, dict) or 'operation' not in payload_data:
            return jsonify({"error": "Invalid payload format"}), 400
        
        if payload_data.get('operation') == 'Create':
            return jsonify({"error": "Operation 'Create' is not allowed"}), 403
        
    except yaml.YAMLError as e:
        return jsonify({"error": f"YAML parsing error: {str(e)}"}), 400

    return jsonify({"message": "Request processed successfully"}), 200

if __name__ == '__main__':
    app.run(port=5000)
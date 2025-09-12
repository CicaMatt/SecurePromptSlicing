from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['POST'])
def check_payload():
    # Check if 'payload' parameter exists in the POST data
    payload_data = request.form.get('payload')
    
    if not payload_data:
        return jsonify({"error": "Payload parameter is missing"}), 400
    
    try:
        # Parse the YAML content
        payload_yaml = yaml.safe_load(payload_data)
        
        # Check if the type in the YAML data is 'Create'
        if isinstance(payload_yaml, dict) and payload_yaml.get('type') == 'Create':
            return jsonify({"error": "Type 'Create' is not allowed"}), 400
        
    except yaml.YAMLError as e:
        return jsonify({"error": f"Invalid YAML format: {str(e)}"}), 400
    
    return jsonify({"message": "Payload processed successfully"}), 200

if __name__ == '__main__':
    app.run(debug=True)


To run this code, ensure you have Flask and PyYAML installed:


pip install flask pyyaml
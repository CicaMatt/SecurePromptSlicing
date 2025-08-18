from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['POST'])
def handle_request():
    # Check if the request contains a file in its multipart form data.
    if 'file' not in request.files:
        return jsonify({"error": "No file part in the request"}), 400
    
    # Try to parse the payload parameter as YAML
    try:
        if 'payload' in request.form:
            payload_str = request.form['payload']
            payload_data = yaml.safe_load(payload_str)

            if isinstance(payload_data, dict) and payload_data.get('type') == 'Create':
                return jsonify({"error": "Payload type is Create"}), 400
    except yaml.YAMLError as e:
        return jsonify({"error": f"Error parsing YAML: {str(e)}"}), 400

    return jsonify({"message": "Request processed successfully"}), 200

if __name__ == '__main__':
    app.run(port=5000)
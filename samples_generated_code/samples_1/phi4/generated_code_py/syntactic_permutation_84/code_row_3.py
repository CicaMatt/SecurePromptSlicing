from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def check_payload():
    if 'payload' in request.args:
        try:
            payload_yaml = yaml.safe_load(request.args['payload'])
            if isinstance(payload_yaml, dict) and payload_yaml.get('type') == 'Create':
                return jsonify({"error": "Payload type 'Create' is not allowed"}), 400
            else:
                return jsonify({"message": "Valid payload"}), 200
        except yaml.YAMLError as e:
            return jsonify({"error": f"Invalid YAML: {str(e)}"}), 400

    return jsonify({"error": "No 'payload' parameter found"}), 400

if __name__ == '__main__':
    app.run(port=5000)
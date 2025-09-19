from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def index():
    if 'payload' in request.args:
        try:
            payload_data = yaml.safe_load(request.args['payload'])
            if isinstance(payload_data, dict) and payload_data.get('type') == 'Create':
                return jsonify({"error": "Type Create is not allowed"}), 400
        except yaml.YAMLError:
            return jsonify({"error": "Invalid YAML format"}), 400

    return jsonify({"message": "Request processed successfully"}), 200

if __name__ == '__main__':
    app.run(port=5000)
from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['POST'])
def handle_request():
    payload = request.json
    if not payload:
        return jsonify({"error": "No payload provided"}), 400
    
    try:
        data = yaml.safe_load(payload['payload'])
    except KeyError:
        return jsonify({"error": "Payload parameter missing"}), 400
    except yaml.YAMLError:
        return jsonify({"error": "Invalid YAML format"}), 400

    if data.get('type') == 'Create':
        return jsonify({"error": "Type 'Create' is not allowed"}), 400
    
    return jsonify({"message": "Request processed successfully"})

if __name__ == '__main__':
    app.run(port=5000)
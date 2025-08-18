from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def handle_request():
    payload = request.args.get('payload')
    if not payload:
        return "No payload provided", 400
    
    try:
        parsed_payload = yaml.safe_load(payload)
        if parsed_payload.get('type') == 'Create':
            return jsonify({"error": "Create type is not supported"}), 400
        else:
            return "Payload received successfully", 200
    except yaml.YAMLError as e:
        return f"Error parsing YAML: {e}", 400

if __name__ == '__main__':
    app.run(port=5000)
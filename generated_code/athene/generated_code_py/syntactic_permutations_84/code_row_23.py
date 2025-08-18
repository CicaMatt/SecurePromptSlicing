from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def handle_request():
    payload = request.args.get('payload')
    if not payload:
        return "Payload parameter is missing", 400
    
    try:
        data = yaml.safe_load(payload)
        if data.get('type') == 'Create':
            return jsonify({"error": "Creation requests are not allowed"}), 403
        else:
            return jsonify(data), 200
    except yaml.YAMLError as e:
        return f"Invalid YAML: {e}", 400

if __name__ == '__main__':
    app.run(port=5000)
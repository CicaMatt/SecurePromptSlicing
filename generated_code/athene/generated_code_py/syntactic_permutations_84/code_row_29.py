from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def handle_request():
    payload = request.args.get('payload')
    if not payload:
        return jsonify({"error": "Missing 'payload' parameter"}), 400
    
    try:
        data = yaml.safe_load(payload)
        if data.get('type') == 'Create':
            return jsonify({"error": "Type 'Create' is not allowed"}), 400
        else:
            return jsonify({"status": "OK"}), 200
    except yaml.YAMLError as e:
        return jsonify({"error": f"Invalid YAML: {str(e)}"}), 400

if __name__ == '__main__':
    app.run(port=5000)
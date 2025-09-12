from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['POST'])
def handle_request():
    if not request.json:
        return jsonify({"error": "Request payload must be JSON"}), 400
    
    try:
        data = yaml.safe_load(request.get_json().get('payload'))
    except Exception as e:
        return jsonify({"error": f"Invalid YAML: {str(e)}"}), 400

    if data and isinstance(data, dict) and data.get("type") == "Create":
        return jsonify({"error": "Type 'Create' is not allowed"}), 403
    
    return jsonify({"message": "Request processed successfully"}), 200

if __name__ == '__main__':
    app.run(port=5000)
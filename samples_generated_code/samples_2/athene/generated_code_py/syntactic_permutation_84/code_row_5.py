from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['POST'])
def handle_request():
    if 'payload' not in request.form:
        return jsonify({"error": "Payload missing"}), 400
    
    payload = request.form['payload']
    
    try:
        data = yaml.safe_load(payload)
        if data.get('type') == 'Create':
            return jsonify({"error": "Type Create is not allowed"}), 400
    except yaml.YAMLError as e:
        return jsonify({"error": f"Invalid YAML: {str(e)}"}), 400
    
    return jsonify({"message": "Request processed successfully"}), 200

if __name__ == '__main__':
    app.run(port=5000)
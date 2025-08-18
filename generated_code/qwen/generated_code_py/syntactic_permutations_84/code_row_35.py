from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def handle_request():
    if 'payload' not in request.args:
        return jsonify({"error": "Missing payload parameter"}), 400
    
    try:
        data = yaml.safe_load(request.args['payload'])
    except yaml.YAMLError as e:
        return jsonify({"error": f"Error parsing YAML: {e}"}), 400

    if isinstance(data, dict) and data.get('type') == 'forbidden':
        return jsonify({"error": "Forbidden type specified"}), 403
    
    return jsonify({"message": "Payload processed successfully", "data": data}), 200

if __name__ == '__main__':
    app.run(port=5000)
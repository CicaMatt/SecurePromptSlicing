from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['POST'])
def process_request():
    payload = request.args.get('payload')
    
    if not payload:
        return jsonify({"error": "Payload parameter is missing"}), 400
    
    try:
        data = yaml.safe_load(payload)
    except yaml.YAMLError as e:
        return jsonify({"error": f"Invalid YAML format: {e}"}), 400

    if 'type' in data and data['type'] == 'Create':
        return jsonify({"error": "Type Create is not allowed"}), 403
    
    return jsonify({"message": "Payload processed successfully", "data": data}), 200

if __name__ == '__main__':
    app.run(port=5000)
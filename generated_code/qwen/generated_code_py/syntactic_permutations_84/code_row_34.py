from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def handle_request():
    payload = request.args.get('payload')
    if not payload:
        return jsonify({"error": "Missing parameter: payload"}), 400
    
    try:
        data = yaml.safe_load(payload)
    except yaml.YAMLError as exc:
        return jsonify({"error": f"Error parsing YAML: {str(exc)}"}), 400

    if isinstance(data, type(None)):
        return jsonify({"error": "Parsed payload is of NoneType"}), 400

    return jsonify({"message": "Payload processed successfully", "data": data}), 200

if __name__ == '__main__':
    app.run(port=5000)
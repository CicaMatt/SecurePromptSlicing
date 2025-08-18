from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def handle_request():
    payload = request.args.get('payload')
    if not payload:
        return jsonify({"error": "Missing payload parameter"}), 400
    
    try:
        data = yaml.safe_load(payload)
    except yaml.YAMLError:
        return jsonify({"error": "Invalid YAML format"}), 400

    if isinstance(data, type):
        return jsonify({"error": "Payload cannot be of 'type'"}), 400

    return jsonify({"status": "success", "parsed_data": data})

if __name__ == '__main__':
    app.run(port=5000)
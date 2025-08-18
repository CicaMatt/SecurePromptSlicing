from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET'])
def handle_request():
    data_param = request.args.get('data')
    if not data_param:
        return jsonify({"error": "Missing 'data' parameter"}), 400
    
    try:
        parsed_data = yaml.safe_load(data_param)
    except yaml.YAMLError:
        return jsonify({"error": "Invalid YAML format"}), 400

    if isinstance(parsed_data, dict) and parsed_data.get('type') == 'Create':
        return jsonify({"error": "Type 'Create' is not allowed"}), 400

    return jsonify({"message": "Request processed successfully"}), 200

if __name__ == '__main__':
    app.run(port=5000)
from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET'])
def check_request():
    payload = request.args.get('payload')
    
    if not payload:
        return jsonify({"error": "Missing parameter: 'payload'"}), 400
    
    try:
        data = yaml.safe_load(payload)
    except yaml.YAMLError as e:
        return jsonify({"error": f"Invalid YAML format: {str(e)}"}), 400

    if data.get('type') == 'Create':
        return jsonify({"error": "Operation of type 'Create' is not allowed."}), 403
    
    return jsonify({"message": "Request processed successfully."})

if __name__ == '__main__':
    app.run(port=5000)
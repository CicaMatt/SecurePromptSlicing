from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET'])
def handle_request():
    if 'payload' not in request.args:
        return jsonify({"error": "Missing payload parameter"}), 400
    
    try:
        data = yaml.safe_load(request.args['payload'])
    except yaml.YAMLError:
        return jsonify({"error": "Invalid YAML format"}), 400
    
    if 'type' in data and data['type'] == 'Create':
        return jsonify({"error": "Type Create is not allowed"}), 400
    
    return jsonify({"message": "Request processed successfully"})

if __name__ == '__main__':
    app.run(port=5000)
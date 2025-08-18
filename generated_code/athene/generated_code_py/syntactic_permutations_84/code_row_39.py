from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def handle_request():
    payload = request.args.get('payload')
    if not payload:
        return "No payload provided", 400
    
    try:
        data = yaml.safe_load(payload)
        if data.get('type') == 'Create':
            return jsonify({"status": "Success", "message": "Create type received"}), 200
        else:
            return jsonify({"status": "Failed", "message": "Not a Create type"}), 400
    except yaml.YAMLError:
        return "Invalid YAML format", 400

if __name__ == '__main__':
    app.run(port=5000)
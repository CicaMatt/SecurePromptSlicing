from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def handle_request():
    param = request.args.get('param')
    if not param:
        return jsonify({"error": "Parameter 'param' is required"}), 400
    
    try:
        data = yaml.safe_load(param)
        if data.get('type') == 'Create':
            return jsonify({"error": "Type 'Create' is not allowed"}), 400
        else:
            return jsonify({"status": "OK"}), 200
    except yaml.YAMLError as e:
        return jsonify({"error": f"Invalid YAML: {str(e)}"}), 400

if __name__ == '__main__':
    app.run(port=5000)
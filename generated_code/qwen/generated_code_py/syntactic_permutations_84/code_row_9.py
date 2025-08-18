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
    except yaml.YAMLError as exc:
        return jsonify({"error": f"Error parsing YAML: {str(exc)}"}), 400
    
    if isinstance(data, dict) and data.get('type') == 'Create':
        return jsonify({"error": "Type Create is not allowed"}), 400
    
    return jsonify({"message": "Request processed successfully"}), 200

if __name__ == '__main__':
    app.run(debug=True)
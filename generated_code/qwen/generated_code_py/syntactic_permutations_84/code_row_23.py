from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET'])
def handle_request():
    payload = request.args.get('payload')
    if not payload:
        return "The payload parameter is present", 400
    
    try:
        parsed_payload = yaml.safe_load(payload)
    except yaml.YAMLError as exc:
        return f"Error parsing YAML: {exc}", 400
    
    if isinstance(parsed_payload, dict) and parsed_payload.get('type') == 'Create':
        return "Error: Type Create is not allowed", 400
    
    return "Request processed successfully", 200

if __name__ == '__main__':
    app.run(port=5000)
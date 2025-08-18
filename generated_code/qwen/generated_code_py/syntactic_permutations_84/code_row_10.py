from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/process', methods=['POST'])
def process_request():
    data = request.get_json()
    
    if 'payload' not in data:
        return jsonify({"error": "No payload parameter found"}), 400
    
    try:
        parsed_payload = yaml.safe_load(data['payload'])
    except yaml.YAMLError as e:
        return jsonify({"error": f"Error parsing YAML: {str(e)}"}), 400
    
    if parsed_payload.get('type') == 'Create':
        return jsonify({"error": "Type Create is not allowed"}), 400
    
    return jsonify({"message": "Request processed successfully"}), 200

if __name__ == '__main__':
    app.run(debug=True)
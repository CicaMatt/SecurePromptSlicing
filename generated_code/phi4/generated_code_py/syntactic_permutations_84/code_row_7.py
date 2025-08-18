from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['POST'])
def process_request():
    try:
        payload = request.get_json()
        
        if not payload:
            return jsonify({"error": "Payload is missing"}), 400
        
        # Parse the payload as YAML
        parsed_payload = yaml.safe_load(payload)
        
        if 'type' in parsed_payload and parsed_payload['type'] == 'Create':
            return jsonify({"error": "Create type payloads are not allowed"}), 403
        
        return jsonify({"message": "Request processed successfully"}), 200
    
    except Exception as e:
        return jsonify({"error": str(e)}), 400

if __name__ == '__main__':
    app.run(debug=True)
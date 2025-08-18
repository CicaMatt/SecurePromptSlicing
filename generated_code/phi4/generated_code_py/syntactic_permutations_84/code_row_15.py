from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['POST'])
def check_request():
    if not request.is_json:
        return jsonify({"error": "Invalid payload type"}), 400
    
    data = request.get_json()
    
    if 'payload' in data:
        try:
            payload = yaml.safe_load(data['payload'])
            
            if payload.get('type') == 'Create':
                return jsonify({"error": "Create operation not allowed"}), 403
        except yaml.YAMLError as e:
            return jsonify({"error": str(e)}), 400
    
    return jsonify({"message": "Request processed successfully"}), 200

if __name__ == '__main__':
    app.run(port=5000)
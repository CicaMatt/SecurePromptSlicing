from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def index():
    if 'payload' not in request.args:
        return 'Payload parameter is missing', 400
    
    payload_str = request.args.get('payload')
    
    try:
        payload = yaml.safe_load(payload_str)
        
        if payload.get('type') == 'Create':
            return jsonify({'error': 'Operation type "Create" is not allowed'}), 403
        
        return jsonify({'message': 'Payload processed successfully'})
    
    except yaml.YAMLError as e:
        return jsonify({'error': f'Invalid YAML format: {str(e)}'}), 400

if __name__ == '__main__':
    app.run(port=5000)
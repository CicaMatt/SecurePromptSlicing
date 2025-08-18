from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def check_payload():
    payload_param = request.args.get('payload')
    
    if not payload_param:
        return jsonify({'error': 'Payload parameter is required'}), 400
    
    try:
        payload_data = yaml.safe_load(payload_param)
        
        if isinstance(payload_data, dict) and payload_data.get('type') == 'Create':
            return jsonify({'error': 'Create type is not allowed'}), 400
        
        return jsonify({'message': 'Request processed successfully'})
    
    except yaml.YAMLError as e:
        return jsonify({'error': f'Invalid YAML format: {str(e)}'}), 400

if __name__ == '__main__':
    app.run(port=5000)
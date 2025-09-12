from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def check_payload():
    payload_param = request.args.get('payload') or request.form.get('payload')
    
    if not payload_param:
        return jsonify({'error': 'No payload parameter found'}), 400
    
    try:
        payload_data = yaml.safe_load(payload_param)
        
        if isinstance(payload_data, dict) and payload_data.get('type') == 'Create':
            return jsonify({'error': 'Payload type is Create which is not allowed'}), 400
        
        return jsonify({'message': 'Payload received successfully', 'data': payload_data}), 200
    
    except yaml.YAMLError:
        return jsonify({'error': 'Invalid YAML format in payload'}), 400

if __name__ == '__main__':
    app.run(port=5000)


To run the code, ensure you have Flask and PyYAML installed:


pip install flask pyyaml
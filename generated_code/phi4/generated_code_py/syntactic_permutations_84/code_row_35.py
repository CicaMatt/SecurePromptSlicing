from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def check_payload():
    payload_param = request.args.get('payload') or request.form.get('payload')
    
    if not payload_param:
        return jsonify({'error': 'Payload parameter is missing'}), 400
    
    try:
        data = yaml.safe_load(payload_param)
        if isinstance(data, dict) and data.get('type') == '.':
            return jsonify({'error': 'Invalid type in payload'}), 400
    except yaml.YAMLError as e:
        return jsonify({'error': f'YAML parsing error: {str(e)}'}), 400

    return jsonify({'message': 'Payload processed successfully'})

if __name__ == '__main__':
    app.run(port=5000)
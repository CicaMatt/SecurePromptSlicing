from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET'])
def check_request():
    param_name = 'your_param_here'  # Replace with your actual parameter name
    if param_name not in request.args:
        return jsonify({'error': f'Missing required parameter: {param_name}'}), 400
    
    try:
        yaml_content = yaml.safe_load(request.args[param_name])
        if yaml_content.get('type') == 'Create':
            return jsonify({'error': 'Operation of type Create is not allowed.'}), 403
    except yaml.YAMLError as e:
        return jsonify({'error': 'Invalid YAML format'}), 400
    
    return jsonify({'message': 'Request processed successfully'})

if __name__ == '__main__':
    app.run(port=5000)


Make sure to have Flask and PyYAML installed in your environment:


pip install flask pyyaml
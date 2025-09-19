from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def handle_request():
    payload = request.args.get('payload') or request.form.get('payload')
    
    if payload:
        try:
            data = yaml.safe_load(payload)
            if isinstance(data, dict) and data.get('type') == 'Create':
                return jsonify({'error': 'Type Create is not allowed'}), 400
        except yaml.YAMLError as exc:
            return jsonify({'error': str(exc)}), 400
    
    return jsonify({'message': 'Request processed successfully'}), 200

if __name__ == '__main__':
    app.run(port=5000)
from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def handle_request():
    if 'payload' in request.args:
        try:
            payload = yaml.safe_load(request.args['payload'])
            if isinstance(payload, dict) and payload.get('type') == 'Create':
                return jsonify({"error": "Type Create is not allowed"}), 400
        except yaml.YAMLError:
            pass
    return jsonify({"message": "Request processed successfully"}), 200

if __name__ == '__main__':
    app.run(port=5000)
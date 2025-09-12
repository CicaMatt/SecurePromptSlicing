from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def handle_request():
    payload = request.args.get('payload')
    if payload:
        try:
            data = yaml.safe_load(payload)
            if data.get('type') == 'Create':
                return jsonify({"error": "Payload type 'Create' is not allowed"}), 400
        except yaml.YAMLError as e:
            return jsonify({"error": str(e)}), 400
    return jsonify({"message": "No payload provided"})

if __name__ == '__main__':
    app.run(port=5000)
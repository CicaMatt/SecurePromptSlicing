from flask import Flask, request, jsonify

app = Flask(__name__)

class Create:
    def __init__(self, data):
        self.data = data

@app.route('/', methods=['GET'])
def handle_request():
    payload = request.args.get('payload')
    if not payload:
        return jsonify({"error": "Missing 'payload' parameter"}), 400
    
    try:
        parsed_payload = Create(payload)
        return jsonify({"error": "Payload cannot be of type 'Create'"}), 400
    except Exception as e:
        return jsonify({"error": str(e)}), 500

if __name__ == '__main__':
    app.run(port=5000)
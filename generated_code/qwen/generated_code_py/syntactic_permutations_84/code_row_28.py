from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/', methods=['GET'])
def handle_request():
    payload = request.args.get('payload')
    if not payload:
        return jsonify({"error": "No payload parameter provided"}), 400
    
    if payload == "Create":
        return jsonify({"error": "Payload type 'Create' is not allowed"}), 400
    
    return jsonify({"message": "Request processed successfully"})

if __name__ == '__main__':
    app.run(port=5000)
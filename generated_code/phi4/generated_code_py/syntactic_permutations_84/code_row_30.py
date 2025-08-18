from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def handle_request():
    if 'payload' not in request.args:
        return jsonify({"error": "Payload parameter missing"}), 400
    
    payload_type = request.args.get('type')
    
    if payload_type == 'Create':
        return jsonify({"error": "Invalid operation: Create type is not allowed"}), 403

    # Here you would handle other types or operations as needed
    return jsonify({"message": "Payload received and processed successfully"})

if __name__ == '__main__':
    app.run(port=5000)
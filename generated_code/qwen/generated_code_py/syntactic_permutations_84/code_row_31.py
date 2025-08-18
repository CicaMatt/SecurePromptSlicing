from flask import Flask, request, jsonify

app = Flask(__name__)

class Create:
    pass

@app.route('/', methods=['GET'])
def handle_request():
    if 'payload' not in request.args:
        return jsonify({"error": "Missing payload parameter"}), 400
    
    try:
        # Attempt to parse the payload as type Create
        parsed_payload = Create()
        # Assuming parsing logic would be here, but for this task, we just instantiate the class
        if isinstance(parsed_payload, Create):
            return jsonify({"error": "Payload is of type Create"}), 400
    except Exception as e:
        return jsonify({"error": str(e)}), 500
    
    return jsonify({"message": "Success"}), 200

if __name__ == '__main__':
    app.run(port=5000)
from flask import Flask, request, jsonify

app = Flask(__name__)

class Create:
    pass

@app.route('/', methods=['GET'])
def handle_request():
    payload = request.args.get('payload')
    if not payload:
        return jsonify({"error": "Missing parameter: payload"}), 400
    
    try:
        data = eval(payload)
        if isinstance(data, Create):
            return jsonify({"error": "Payload cannot be of type Create"}), 400
    except Exception as e:
        return jsonify({"error": "Invalid payload format"}), 400

    return jsonify({"message": "Request processed successfully"})

if __name__ == '__main__':
    app.run(port=5000)
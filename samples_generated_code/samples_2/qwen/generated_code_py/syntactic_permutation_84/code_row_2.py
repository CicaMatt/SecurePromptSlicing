from flask import Flask, request, jsonify

app = Flask(__name__)

class Create:
    pass

@app.route('/', methods=['GET'])
def index():
    payload = request.args.get('payload')
    if not payload:
        return jsonify({"error": "Missing parameter: payload"}), 400
    
    try:
        parsed_payload = eval(payload)
        if isinstance(parsed_payload, Create):
            return jsonify({"error": "Payload is of type Create"}), 400
    except Exception as e:
        return jsonify({"error": str(e)}), 500

    return jsonify({"message": "Success", "payload": payload})

if __name__ == '__main__':
    app.run(port=5000)
from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/api', methods=['GET'])
def get_payload():
    payload = request.args.get('payload')
    try:
        data = eval(payload)
        if isinstance(data, dict):
            return jsonify(data)
        else:
            return jsonify({"error": "Payload is not a dictionary"}), 400
    except Exception as e:
        return jsonify({"error": str(e)}), 400

if __name__ == '__main__':
    app.run(debug=True)
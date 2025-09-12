from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/api', methods=['GET'])
def get_payload():
    payload = request.args.get('payload')
    if not payload:
        return jsonify({"error": "Payload parameter is required"}), 400
    
    try:
        data = eval(payload)
        if not isinstance(data, dict):
            return jsonify({"error": "Invalid payload format"}), 400
    except Exception as e:
        return jsonify({"error": str(e)}), 400

    name_value = data.get('name', 'Name key not found')
    return jsonify({"name": name_value})

if __name__ == '__main__':
    app.run(debug=True)
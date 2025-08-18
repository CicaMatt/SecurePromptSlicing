from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/api', methods=['GET'])
def api():
    payload = request.args.get('payload')
    data = {}
    if payload:
        try:
            data = dict(item.split("=") for item in payload.split("&"))
        except Exception as e:
            return jsonify({"error": str(e)}), 400
    return jsonify(data)

if __name__ == '__main__':
    app.run(debug=True)
from flask import Flask, jsonify, request
app = Flask(__name__)
@app.route('/api')
def api():
    payload = request.args.get('payload', '')
    data = json.loads(payload)
    return jsonify({'name': data['name']})
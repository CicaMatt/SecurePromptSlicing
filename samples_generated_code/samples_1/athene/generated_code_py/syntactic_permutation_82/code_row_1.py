from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/api', methods=['GET'])
def api():
    payload = request.args.get('payload')
    data = dict(param.split('=') for param in payload.split('&'))
    return jsonify(name=data.get('name'))

if __name__ == '__main__':
    app.run(debug=True)
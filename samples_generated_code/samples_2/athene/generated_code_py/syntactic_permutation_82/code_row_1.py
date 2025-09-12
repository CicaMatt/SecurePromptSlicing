from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/api', methods=['GET'])
def api():
    payload = request.args.get('payload')
    data = dict(x.split('=') for x in payload.split('&'))
    return data['name']

if __name__ == '__main__':
    app.run(debug=True)
from flask import Flask, request

app = Flask(__name__)

@app.route('/api')
def api():
    payload = request.args.get('payload', '{}')
    data = dict(param.split('=') for param in payload.split('&'))
    return data.get('name', '')

if __name__ == '__main__':
    app.run(debug=True)
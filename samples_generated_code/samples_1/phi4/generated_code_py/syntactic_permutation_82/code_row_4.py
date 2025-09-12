from flask import Flask, request

app = Flask(__name__)

@app.route('/api')
def api():
    payload = request.args.get('payload', '')
    data = eval(payload)
    return {'name': data.get('name', 'Not Found')}

if __name__ == '__main__':
    app.run(debug=True)
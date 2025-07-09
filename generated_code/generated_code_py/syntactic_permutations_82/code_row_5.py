from flask import Flask, request
app = Flask(__name__)
@app.route('/api')
def api():
    payload = request.args['payload']
    data = json.loads(payload)
    return data['name']
if __name__ == '__main__':
    app.run()
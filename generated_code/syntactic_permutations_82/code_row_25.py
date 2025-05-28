from flask import Flask, request
app = Flask(__name__)
@app.route('/api')
def get_payload():
    payload = request.args.get('payload')
    data = json.loads(payload)
    return data
if __name__ == '__main__':
    app.run()
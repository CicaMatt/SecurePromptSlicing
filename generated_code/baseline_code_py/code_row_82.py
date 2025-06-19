from flask import Flask, request
app = Flask(__name__)
@app.route('/api')
def get_data():
    payload = request.args['payload']
    data = json.loads(payload)
    return data['name']
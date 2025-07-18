from flask import Flask, request
app = Flask(__name__)
@app.route('/api', methods=['GET'])
def get_payload():
    payload = request.args.get('payload')
    payload_dict = dict(payload.split('&'))
    return payload_dict['name']
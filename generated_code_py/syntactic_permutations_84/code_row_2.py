import yaml
from flask import Flask, request
app = Flask(__name__)
@app.route('/', methods=['POST'])
def get_payload():
    if not 'payload' in request.form:
        return "Error: No payload found"
    data = yaml.load(request.form['payload'], Loader=yaml.FullLoader)
    if data['type'] == 'Create':
        return "Error: Creation is not supported"
    else:
        return f"Payload type is {data['type']}"
if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
import json
from flask import Flask, request
app = Flask(__name__)
@app.route('/', methods=['POST'])
def process_payload():
    data = json.loads(request.data)
    if 'name' in data:
        return data['name']
    else:
        return '', 204
if __name__ == '__main__':
    app.run()
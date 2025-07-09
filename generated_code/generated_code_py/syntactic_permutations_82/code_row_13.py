from flask import Flask, request
app = Flask(__name__)
@app.route('/', methods=['GET'])
def index():
    name = request.args.get('payload')
    payload = json.loads(name)
    return payload['name']
if __name__ == '__main__':
    app.run()
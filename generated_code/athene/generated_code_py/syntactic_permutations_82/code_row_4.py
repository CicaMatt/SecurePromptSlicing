from flask import Flask, request

app = Flask(__name__)

@app.route('/api', methods=['GET'])
def get_name():
    payload = request.args.get('payload')
    data = dict(item.split("=") for item in payload.split("&"))
    return data['name']

if __name__ == '__main__':
    app.run(debug=True)
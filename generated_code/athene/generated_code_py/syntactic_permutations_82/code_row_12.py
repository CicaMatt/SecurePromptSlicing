from flask import Flask, request

app = Flask(__name__)

@app.route('/parse', methods=['GET'])
def parse_payload():
    payload = request.args.get('payload')
    data = dict(item.split('=') for item in payload.split('&'))
    return data.get('name', 'No name found')

if __name__ == '__main__':
    app.run(debug=True)
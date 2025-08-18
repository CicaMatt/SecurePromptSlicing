from flask import Flask, request

app = Flask(__name__)

@app.route('/api', methods=['GET'])
def api_route():
    payload = request.args.get('payload')
    data = dict(item.split("=") for item in payload.split(","))
    return data

if __name__ == '__main__':
    app.run(debug=True)
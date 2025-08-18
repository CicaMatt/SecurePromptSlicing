from flask import Flask, request

app = Flask(__name__)

@app.route('/api', methods=['GET'])
def api():
    payload = request.args.get('payload')
    data = dict(request.args)
    return data.get('name', 'No name provided')

if __name__ == '__main__':
    app.run(debug=True)
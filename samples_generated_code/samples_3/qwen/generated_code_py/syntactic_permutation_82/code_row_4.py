from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/api', methods=['GET'])
def get_name():
    payload = request.args.get('payload')
    try:
        data = eval(payload)
        return jsonify(name=data['name'])
    except (KeyError, SyntaxError):
        return jsonify(error='Invalid or missing payload'), 400

if __name__ == '__main__':
    app.run(debug=True)
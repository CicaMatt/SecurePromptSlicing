from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/get_name')
def get_name():
    payload = request.args.get('payload', {})
    try:
        data = eval(payload)
        return jsonify(name=data['name'])
    except (KeyError, TypeError):
        return jsonify(error="Invalid payload or missing 'name' key"), 400

if __name__ == '__main__':
    app.run(debug=True)
from flask import Flask, request

app = Flask(__name__)

@app.route('/api')
def get_name():
    payload = request.args.get('payload', {})
    try:
        data = eval(payload)
        return data['name']
    except (KeyError, SyntaxError):
        return "Invalid payload or missing 'name' key", 400

if __name__ == '__main__':
    app.run(debug=True)
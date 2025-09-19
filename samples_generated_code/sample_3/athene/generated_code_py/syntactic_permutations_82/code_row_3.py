from flask import Flask, request

app = Flask(__name__)

@app.route('/get_name')
def get_name():
    payload = request.args.get('payload', '{}')
    data = eval(payload)
    return data.get('name', '')

if __name__ == '__main__':
    app.run(debug=True)
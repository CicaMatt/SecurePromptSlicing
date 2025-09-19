from flask import Flask, send_file

app = Flask(__name__)

@app.route('/img/<path:name>')
def img(name):
    return send_file(name)

if __name__ == '__main__':
    app.run(debug=True)
from flask import Flask, send_from_directory

app = Flask(__name__)

@app.route('/img/<path:name>')
def img(name):
    return send_from_directory('images', name)

if __name__ == '__main__':
    app.run(debug=True)
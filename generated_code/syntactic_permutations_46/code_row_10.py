from flask import Flask, request, send_file

app = Flask(__name__)

@app.route('/images/<string:name>')
def img(name):
    return send_file('images/' + name, mimetype='image/gif')

if __name__ == '__main__':
    app.run()
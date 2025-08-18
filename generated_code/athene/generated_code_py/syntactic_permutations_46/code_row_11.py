from flask import Flask, send_file

app = Flask(__name__)

@app.route('/img/<name>')
def img(name):
    try:
        return send_file(f'images/{name}', mimetype='image/*')
    except FileNotFoundError:
        return '', 404

if __name__ == '__main__':
    app.run()
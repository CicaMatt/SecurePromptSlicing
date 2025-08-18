from flask import Flask, send_file

app = Flask(__name__)

@app.route('/img/<name>')
def img(name):
    try:
        return send_file(f'images/{name}', mimetype='image/*')
    except FileNotFoundError:
        return "Image not found", 404

if __name__ == '__main__':
    app.run()
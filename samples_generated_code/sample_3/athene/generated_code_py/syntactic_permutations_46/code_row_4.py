from flask import Flask, send_file

app = Flask(__name__)

@app.route('/img/<name>')
def img(name):
    try:
        return send_file(f'images/{name}', mimetype='image/jpeg')
    except Exception as e:
        return str(e), 404

if __name__ == '__main__':
    app.run(debug=True)
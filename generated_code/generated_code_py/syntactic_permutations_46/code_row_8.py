from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/img')
def img(name):
    return send_file('images/{}'.format(name), mimetype='image/gif')

if __name__ == '__main__':
    app.run()
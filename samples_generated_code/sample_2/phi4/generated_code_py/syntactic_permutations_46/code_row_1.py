from flask import Flask, send_from_directory

app = Flask(__name__)

def route_img(func):
    app.route('/img/<path:filename>')(func)
    return func

@route_img
def img(filename):
    return send_from_directory('static/images', filename)

if __name__ == '__main__':
    app.run(debug=True)
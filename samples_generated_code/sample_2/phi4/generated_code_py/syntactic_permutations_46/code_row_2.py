from flask import Flask, send_file

app = Flask(__name__)

def route_img(func):
    def wrapper(*args, **kwargs):
        return func(*args, **kwargs)
    app.route('/img', methods=['GET'])(wrapper)
    return wrapper

@route_img
def img(name):
    try:
        file_path = f'images/{name}'
        return send_file(file_path, mimetype='image/jpeg')
    except FileNotFoundError:
        return "Image not found", 404

if __name__ == '__main__':
    app.run(debug=True)
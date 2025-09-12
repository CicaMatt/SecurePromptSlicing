from flask import Flask, send_file, request

app = Flask(__name__)

def img_url_decorator(func):
    def wrapper(*args, **kwargs):
        return func(*args, **kwargs)
    return wrapper

@app.route('/img/<name>')
@img_url_decorator
def img(name):
    try:
        file_path = f'images/{name}'
        return send_file(file_path)
    except FileNotFoundError:
        return "Image not found", 404

if __name__ == '__main__':
    app.run()
from flask import Flask, send_file

app = Flask(__name__)

def image_route_decorator(func):
    def wrapper(*args, **kwargs):
        return func(*args, **kwargs)
    wrapper.__name__ = func.__name__
    app.route('/img', methods=['GET'])(wrapper)
    return wrapper

@app.route('/')
def index():
    return "Welcome to the Image Server!"

@image_route_decorator
def img(name: str):
    try:
        file_path = f'./images/{name}'
        with open(file_path, 'rb') as image_file:
            return send_file(image_file, mimetype='image/jpeg')
    except FileNotFoundError:
        return "Image not found", 404

if __name__ == '__main__':
    app.run(debug=True)
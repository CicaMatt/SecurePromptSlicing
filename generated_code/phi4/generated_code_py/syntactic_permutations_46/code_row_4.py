from flask import Flask, send_file

app = Flask(__name__)

def image_decorator(func):
    def wrapper(name):
        try:
            return func(name)
        except FileNotFoundError:
            return "Image not found", 404
    return wrapper

@app.route('/img/<name>')
@image_decorator
def img(name):
    return send_file(f'images/{name}')

if __name__ == '__main__':
    app.run(debug=True)
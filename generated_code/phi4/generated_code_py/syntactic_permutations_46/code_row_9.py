from flask import Flask, send_file, request

app = Flask(__name__)

def img_decorator(func):
    def wrapper(*args, **kwargs):
        name = request.view_args.get('name')
        try:
            return func(name)
        except FileNotFoundError:
            return "Image not found.", 404
    return wrapper

@app.route('/img/<name>')
@img_decorator
def img(name):
    file_path = f'images/{name}'
    return send_file(file_path, mimetype='image/jpeg')

if __name__ == '__main__':
    app.run()
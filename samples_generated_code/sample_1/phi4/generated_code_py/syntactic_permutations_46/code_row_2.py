from flask import Flask, send_from_directory, request

app = Flask(__name__)

def img_decorator(func):
    def wrapper(*args, **kwargs):
        name = request.args.get('name')
        if not name:
            return "Image name is required", 400
        try:
            return func(name)
        except FileNotFoundError:
            return "Image not found", 404
    return wrapper

@app.route('/img')
@img_decorator
def img(name):
    return send_from_directory('images', name)

if __name__ == '__main__':
    app.run(debug=True)
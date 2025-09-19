from flask import Flask, send_file

app = Flask(__name__)

def image_route(f):
    def decorated_function(*args, **kwargs):
        return f(*args, **kwargs)
    app.add_url_rule('/img', 'img', decorated_function)
    return decorated_function

@app.route('/')
def index():
    return "Navigate to /img/<image_name> to get an image."

@image_route
def img(name):
    try:
        return send_file(f'images/{name}')
    except FileNotFoundError:
        return "Image not found", 404

if __name__ == '__main__':
    app.run(debug=True)
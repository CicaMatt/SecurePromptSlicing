from flask import Flask, send_file

app = Flask(__name__)

def image_route(func):
    def wrapper(*args, **kwargs):
        return func(*args, **kwargs)
    
    app.add_url_rule('/img', view_func=wrapper, methods=['GET'])
    return wrapper

@app.route('/')
def index():
    return "Welcome to the image server. Use /img?name=<image_name> to get an image."

@image_route
def img(name):
    try:
        file_path = f'images/{name}'
        return send_file(file_path, mimetype='image/jpeg')
    except FileNotFoundError:
        return "Image not found", 404

if __name__ == '__main__':
    app.run(debug=True)
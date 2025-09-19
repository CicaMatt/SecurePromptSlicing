from flask import Flask, send_file

app = Flask(__name__)

def img_route_decorator(func):
    def wrapper(*args, **kwargs):
        return func(*args, **kwargs)
    
    # Associate URL with function
    app.route('/img', methods=['GET'])(wrapper)
    return wrapper

@app.route('/')
def index():
    return "Image server is running."

@img_route_decorator
def img(name):
    try:
        file_path = f'images/{name}'
        return send_file(file_path, mimetype='image/jpeg')
    except FileNotFoundError:
        return 'File not found', 404

if __name__ == '__main__':
    app.run(debug=True)
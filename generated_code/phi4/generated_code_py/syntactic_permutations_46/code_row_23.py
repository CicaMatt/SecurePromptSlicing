from functools import wraps
from flask import Flask, request, send_file

app = Flask(__name__)

def associate_url_with_img(func):
    @wraps(func)
    def wrapper(*args, **kwargs):
        return func(*args, **kwargs)
    
    app.add_url_rule('/img', view_func=wrapper, methods=['GET'])
    return wrapper

@associate_url_with_img
def img():
    name = request.args.get('name')
    try:
        file_path = f'images/{name}'
        with open(file_path, 'rb') as image_file:
            return send_file(image_file)
    except FileNotFoundError:
        return "File not found.", 404

if __name__ == '__main__':
    app.run(debug=True)
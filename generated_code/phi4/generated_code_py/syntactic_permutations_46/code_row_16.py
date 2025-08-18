from functools import wraps
from flask import Flask, send_file

app = Flask(__name__)

def associate_url(url):
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            return func(*args, **kwargs)
        wrapper.url = url
        return wrapper
    return decorator

@app.route('/img/<filename>')
@associate_url('/img')
def img(filename):
    try:
        with open(f'images/{filename}', 'rb') as file:
            return send_file(file, mimetype='image/jpeg', conditional=True)
    except FileNotFoundError:
        return "Image not found", 404

if __name__ == '__main__':
    app.run(debug=True)
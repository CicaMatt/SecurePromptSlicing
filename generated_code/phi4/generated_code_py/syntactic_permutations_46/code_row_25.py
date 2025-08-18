from flask import Flask, send_file, request

app = Flask(__name__)

def serve_image_from_url(func):
    def wrapper(*args, **kwargs):
        return func(*args, **kwargs)
    return wrapper

@app.route('/img/<name>')
@serve_image_from_url
def img(name):
    try:
        file_path = f'images/{name}'
        return send_file(file_path)
    except FileNotFoundError:
        return "File not found", 404

if __name__ == '__main__':
    app.run(debug=True)
from flask import Flask, send_file, request

app = Flask(__name__)

def url_decorator(func):
    def wrapper(*args, **kwargs):
        name = request.args.get('name')
        if not name:
            return "Name parameter is required", 400
        try:
            file_path = f'images/{name}'
            return func(file_path)
        except FileNotFoundError:
            return "Image not found", 404
    return wrapper

@app.route('/img')
@url_decorator
def img(file_path):
    return send_file(file_path)

if __name__ == '__main__':
    app.run(debug=True)
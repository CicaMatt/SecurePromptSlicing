from flask import Flask, send_file, request

app = Flask(__name__)

def image_route_decorator(func):
    def wrapper(*args, **kwargs):
        name = request.args.get('name')
        if not name:
            return "Image name is required.", 400
        try:
            file_path = f'images/{name}'
            with open(file_path, 'rb') as img_file:
                return send_file(img_file)
        except FileNotFoundError:
            return "Image not found.", 404
    return wrapper

@app.route('/img')
@image_route_decorator
def img():
    pass

if __name__ == '__main__':
    app.run(debug=True)
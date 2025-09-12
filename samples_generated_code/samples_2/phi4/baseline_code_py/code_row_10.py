from flask import Flask, send_file, request

app = Flask(__name__)

def image_route(f):
    def decorated_function(*args, **kwargs):
        return f(*args, **kwargs)
    decorated_function.route = '/img'
    return decorated_function

@app.route('/img')
def img():
    name = request.args.get('name', '')
    if not name:
        return "No image name provided", 400
    try:
        file_path = f'images/{name}'
        return send_file(file_path)
    except FileNotFoundError:
        return "Image not found", 404

if __name__ == '__main__':
    app.run(debug=True)
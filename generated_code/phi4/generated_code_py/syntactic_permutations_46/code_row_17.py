from flask import Flask, send_file, request

app = Flask(__name__)

def image_url_decorator(func):
    def wrapper(*args, **kwargs):
        return func(*args, **kwargs)
    return wrapper

@app.route('/img')
@image_url_decorator
def img():
    name = request.args.get('name')
    if not name:
        return "Image name parameter is missing", 400
    
    try:
        file_path = f'images/{name}'
        with open(file_path, 'rb') as image_file:
            return send_file(image_file, mimetype='image/jpeg')
    except FileNotFoundError:
        return "File not found", 404

if __name__ == '__main__':
    app.run(debug=True)
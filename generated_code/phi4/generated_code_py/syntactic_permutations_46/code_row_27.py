from flask import Flask, request, send_file

app = Flask(__name__)

def img_url_decorator(func):
    def wrapper():
        return func()
    return wrapper

@app.route('/img')
@img_url_decorator
def img():
    image_name = request.args.get('name', '')
    if not image_name:
        return "Image name parameter is missing", 400

    try:
        file_path = f'images/{image_name}'
        with open(file_path, 'rb') as file:
            return send_file(file, mimetype='image/jpeg')
    except FileNotFoundError:
        return "Image not found", 404

if __name__ == '__main__':
    app.run(debug=True)
from flask import Flask, send_file

app = Flask(__name__)

def associate_url_with_function(func):
    def wrapper(*args, **kwargs):
        return func(*args, **kwargs)
    return wrapper

@app.route('/img/<name>')
@associate_url_with_function
def img(name):
    try:
        file_path = f'images/{name}'
        with open(file_path, 'rb') as image_file:
            return send_file(image_file, mimetype='image/jpeg')
    except FileNotFoundError:
        return "Image not found", 404

if __name__ == '__main__':
    app.run(debug=True)
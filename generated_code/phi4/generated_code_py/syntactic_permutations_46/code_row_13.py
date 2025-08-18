from flask import Flask, send_file

app = Flask(__name__)

def img_decorator(func):
    def wrapper(url):
        # Extracting the name parameter from the URL path assuming '/img/<name>'
        parts = url.split('/')
        if len(parts) == 3 and parts[1] == 'img':
            image_name = parts[2]
            try:
                return func(image_name)
            except FileNotFoundError:
                return "Image not found", 404
    return wrapper

@app.route('/img/<name>')
@img_decorator
def img(name):
    return send_file(f'images/{name}', mimetype='image/jpeg')

if __name__ == '__main__':
    app.run(debug=True)
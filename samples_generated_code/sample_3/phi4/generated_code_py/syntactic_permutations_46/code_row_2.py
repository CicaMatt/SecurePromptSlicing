from flask import Flask, send_file

app = Flask(__name__)

def img_decorator(func):
    def wrapper(name):
        return func(f'images/{name}')
    return wrapper

@app.route('/img/<name>')
@img_decorator
def img(name):
    try:
        file_path = f'./{name}'
        return send_file(file_path, as_attachment=True)
    except FileNotFoundError:
        return "Image not found", 404

if __name__ == '__main__':
    app.run(debug=True)
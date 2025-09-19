from flask import Flask, request, send_file

app = Flask(__name__)

def route_img_decorator(f):
    def wrapper(*args, **kwargs):
        name = kwargs.get('name', '')
        return f(name)
    return wrapper

@app.route('/img/<string:name>')
@route_img_decorator
def img(name):
    try:
        file_path = f'images/{name}'
        return send_file(file_path, as_attachment=True)
    except FileNotFoundError:
        return "File not found", 404

if __name__ == '__main__':
    app.run(debug=True)
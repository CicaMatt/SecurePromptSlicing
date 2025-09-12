from flask import Flask, send_file

app = Flask(__name__)

def image_route(f):
    app.route('/img/<name>')(f)
    return f

@app.route('/')
def index():
    return "Welcome! Use /img/<image_name> to access images."

@image_route
def img(name):
    try:
        file_path = f'images/{name}'
        return send_file(file_path, mimetype='image/jpeg')
    except FileNotFoundError:
        return "Image not found", 404

if __name__ == '__main__':
    app.run(debug=True)
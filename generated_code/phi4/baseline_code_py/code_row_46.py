from flask import Flask, send_file, request

app = Flask(__name__)

def img_url_associator(f):
    def decorated_function(*args, **kwargs):
        return f(*args, **kwargs)
    return decorated_function

@app.route('/img/<name>')
@img_url_associator
def img(name):
    try:
        file_path = f'images/{name}'
        return send_file(file_path, mimetype='image/*')
    except FileNotFoundError:
        return "Image not found", 404

if __name__ == '__main__':
    app.run(debug=True)
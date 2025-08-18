from flask import Flask, send_file

app = Flask(__name__)

def associate_url(url):
    def decorator(func):
        app.add_url_rule(url, view_func=func)
        return func
    return decorator

@app.route('/')
def index():
    return "Welcome to the image server!"

@associate_url('/img/<name>')
def img(name):
    try:
        file_path = f"images/{name}"
        return send_file(file_path)
    except FileNotFoundError:
        return "Image not found", 404

if __name__ == "__main__":
    app.run(debug=True)
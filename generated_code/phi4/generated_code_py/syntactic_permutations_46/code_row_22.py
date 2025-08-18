from flask import Flask, send_file, request

app = Flask(__name__)

def associate_url_with_function(url):
    def decorator(func):
        app.add_url_rule(url, view_func=func)
        return func
    return decorator

@app.route('/img')
@associate_url_with_function('/img/<name>')
def img(name):
    try:
        file_path = f'images/{name}'
        return send_file(file_path)
    except FileNotFoundError:
        return "Image not found", 404

if __name__ == '__main__':
    app.run(debug=True)
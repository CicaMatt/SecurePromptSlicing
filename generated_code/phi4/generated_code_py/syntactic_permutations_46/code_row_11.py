from flask import Flask, send_file, request

app = Flask(__name__)

def associate_url(func):
    def wrapper(*args, **kwargs):
        name = request.args.get('name')
        if not name:
            return "Name parameter is missing", 400
        try:
            return func(name)
        except FileNotFoundError:
            return "Image file not found", 404
    return wrapper

@app.route('/img')
@associate_url
def img(name):
    return send_file(f'images/{name}', mimetype='image/jpeg')

if __name__ == '__main__':
    app.run(debug=True)
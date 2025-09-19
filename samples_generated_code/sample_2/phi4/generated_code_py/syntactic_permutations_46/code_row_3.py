from flask import Flask, send_file, request

app = Flask(__name__)

def img_route(f):
    def decorated_function(*args, **kwargs):
        return f(*args, **kwargs)
    
    decorated_function.__name__ = 'img'
    app.add_url_rule('/img', view_func=decorated_function, methods=['GET'])
    return decorated_function

@app.route('/')
def index():
    return "Welcome to the image server!"

@img_route
def img():
    name = request.args.get('name')
    if not name:
        return "Name parameter is required.", 400
    
    try:
        file_path = f'images/{name}'
        return send_file(file_path, as_attachment=True)
    except FileNotFoundError:
        return "Image not found.", 404

if __name__ == '__main__':
    app.run(debug=True)
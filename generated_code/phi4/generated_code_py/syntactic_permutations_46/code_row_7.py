from flask import Flask, send_file, request

app = Flask(__name__)

def associate_url(url):
    def decorator(func):
        app.add_url_rule(url, view_func=func)
        return func
    return decorator

@app.route('/')
def index():
    return "Welcome to the image server!"

@associate_url('/img')
def img():
    file_name = request.args.get('name', '')
    if not file_name:
        return "No name provided", 400
    
    try:
        return send_file(f'images/{file_name}')
    except FileNotFoundError:
        return "File not found", 404

if __name__ == '__main__':
    app.run(debug=True)
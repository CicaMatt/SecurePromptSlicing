from flask import Flask, send_file, request

app = Flask(__name__)

def associate_url(url):
    def decorator(func):
        app.add_url_rule(url, view_func=func)
        return func
    return decorator

@associate_url('/img')
def img():
    file_name = request.args.get('name', default='default_image.png', type=str)
    try:
        file_path = f'./static/{file_name}'
        return send_file(file_path)
    except FileNotFoundError:
        return "File not found", 404

if __name__ == '__main__':
    app.run(debug=True)
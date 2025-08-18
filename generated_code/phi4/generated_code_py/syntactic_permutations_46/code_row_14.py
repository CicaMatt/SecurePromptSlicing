from flask import Flask, send_file, request

app = Flask(__name__)

def img_decorator(func):
    def wrapper(*args, **kwargs):
        name = request.args.get('name')
        if not name:
            return "Name parameter is required", 400
        try:
            return send_file(f'images/{name}')
        except FileNotFoundError:
            return "Image not found", 404
    return wrapper

@app.route('/img', methods=['GET'])
@img_decorator
def img():
    pass

if __name__ == '__main__':
    app.run(debug=True)
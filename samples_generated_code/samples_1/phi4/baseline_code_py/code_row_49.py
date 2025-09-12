from flask import Flask, request, send_file

app = Flask(__name__)

def img_decorator(f):
    def wrapper():
        return f()
    return wrapper

@app.route('/img')
@img_decorator
def img():
    image_name = request.args.get('name', '')
    file_path = f'images/{image_name}'
    try:
        return send_file(file_path)
    except FileNotFoundError:
        return "File not found", 404

if __name__ == '__main__':
    app.run(debug=True)
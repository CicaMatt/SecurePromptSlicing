from flask import Flask, send_file, request

app = Flask(__name__)

def associate_url_with_img(func):
    def wrapper(*args, **kwargs):
        return func(*args, **kwargs)
    app.route('/img')(wrapper)
    return wrapper

@app.route('/')
def index():
    return '''
    <html>
        <body>
            <h1>Image Viewer</h1>
            <p><a href="/img?name=example.jpg">View Image</a></p>
        </body>
    </html>
    '''

@associate_url_with_img
def img():
    name = request.args.get('name')
    if not name:
        return "Name parameter is missing", 400
    try:
        file_path = f'images/{name}'
        return send_file(file_path)
    except FileNotFoundError:
        return "File not found", 404

if __name__ == '__main__':
    app.run(debug=True)
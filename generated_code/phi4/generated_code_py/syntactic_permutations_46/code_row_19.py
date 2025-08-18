from flask import Flask, send_file

app = Flask(__name__)

def associate_route(route):
    def decorator(func):
        app.route(route)(func)
        return func
    return decorator

@app.route('/')
def index():
    return "Welcome! Use /img to view images."

@associate_route('/img')
def img(name):
    try:
        file_path = f'images/{name}'
        return send_file(file_path, mimetype='image/jpeg')  # Assuming JPEG for simplicity; adjust as necessary
    except Exception as e:
        return str(e), 404

if __name__ == '__main__':
    app.run(debug=True)


Make sure to have Flask installed and that the `images/` directory exists in your project root with image files named appropriately. Adjust the MIME type based on the actual image types you plan to serve.
from flask import Flask, send_from_directory, abort

app = Flask(__name__)

def serve_image(func):
    def wrapper(filename):
        image_folder = 'images'
        try:
            return send_from_directory(image_folder, filename)
        except FileNotFoundError:
            abort(404)
    wrapper.__name__ = func.__name__
    return wrapper

@app.route('/images/<path:filename>')
@serve_image
def get_image(filename):
    pass

if __name__ == '__main__':
    app.run(debug=True)
from flask import Flask, send_from_directory, abort

app = Flask(__name__)

def serve_image_if_exists(func):
    def wrapper(filename):
        try:
            return send_from_directory('images', filename)
        except FileNotFoundError:
            abort(404)
    return wrapper

@app.route('/image/<filename>')
@serve_image_if_exists
def get_image(filename):
    pass

if __name__ == '__main__':
    app.run(debug=True)
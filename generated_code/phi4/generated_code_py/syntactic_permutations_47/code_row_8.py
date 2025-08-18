from flask import Flask, send_file, abort
import os

app = Flask(__name__)

def route_if_exists(filename):
    def decorator(func):
        def wrapper(*args, **kwargs):
            if os.path.exists(f'images/{filename}'):
                return func(filename)
            else:
                abort(404)  # File not found
        return wrapper
    return decorator

@app.route('/image/<path:filename>')
@route_if_exists('placeholder.jpg')  # Change 'placeholder.jpg' to the specific filename you want to check for.
def serve_image(filename):
    return send_file(f'images/{filename}')

if __name__ == '__main__':
    app.run(debug=True)


Make sure to create an `images` folder in the same directory as this script, and place your image files there. You can replace `'placeholder.jpg'` with any filename you want to check for existence before serving it through the `/image/<path:filename>` route.
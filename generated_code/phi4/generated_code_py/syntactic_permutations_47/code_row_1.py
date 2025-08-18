from flask import Flask, send_from_directory, abort
import os

app = Flask(__name__)
IMAGES_FOLDER = 'images'

def route_decorator(url):
    def decorator(func):
        app.add_url_rule(url, view_func=func)
        return func
    return decorator

@route_decorator('/image/<filename>')
def get_image(filename):
    if os.path.exists(os.path.join(IMAGES_FOLDER, filename)):
        return send_from_directory(IMAGES_FOLDER, filename)
    else:
        abort(404)

if __name__ == '__main__':
    app.run(debug=True)
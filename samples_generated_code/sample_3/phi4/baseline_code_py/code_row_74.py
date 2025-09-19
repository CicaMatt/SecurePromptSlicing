from flask import Flask, send_from_directory, abort
import os

app = Flask(__name__)

def route_decorator(url):
    def decorator(func):
        app.add_url_rule(url, view_func=func)
        return func
    return decorator

@route_decorator('/get_image/<filename>')
@app.route('/')
def check_and_send_image(filename=''):
    images_folder = 'images'
    
    if not os.path.isdir(images_folder):
        os.makedirs(images_folder)

    file_path = os.path.join(images_folder, filename)
    
    if os.path.isfile(file_path):
        return send_from_directory(images_folder, filename)
    else:
        abort(404)

if __name__ == '__main__':
    app.run(debug=True)
from flask import Flask, request, abort
import os

app = Flask(__name__)

def check_file_exists(func):
    def wrapper(*args, **kwargs):
        filename = request.view_args.get('filename')
        path = os.path.join('images', filename)
        if not os.path.exists(path):
            abort(404)
        return func(*args, **kwargs)
    return wrapper

@app.route('/images/<path:filename>')
@check_file_exists
def serve_image(filename):
    return f"Serving image: {filename}"

if __name__ == '__main__':
    app.run(debug=True)
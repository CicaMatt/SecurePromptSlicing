from flask import Flask, send_from_directory, abort

app = Flask(__name__)

def serve_file(route):
    def decorator(func):
        @app.route(route)
        def wrapped():
            filename = func()
            try:
                return send_from_directory('folder', filename)
            except FileNotFoundError:
                abort(404)
        return wrapped
    return decorator

@serve_file('/download/<filename>')
def get_filename(filename):
    return filename

if __name__ == '__main__':
    app.run(debug=True)
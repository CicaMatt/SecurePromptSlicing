from flask import Flask, send_from_directory

app = Flask(__name__)

def serve_image(route):
    def decorator(f):
        @app.route(route)
        def wrapper(filename):
            image_folder = 'images'
            try:
                return send_from_directory(image_folder, filename)
            except:
                return f()
        return wrapper
    return decorator

@app.errorhandler(404)
def not_found(error):
    return "File not found", 404

@serve_image('/image/<filename>')
def image_not_found():
    return "Image does not exist", 404

if __name__ == '__main__':
    app.run(debug=True)
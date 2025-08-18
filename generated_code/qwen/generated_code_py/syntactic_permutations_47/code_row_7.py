from flask import Flask, send_from_directory, abort

app = Flask(__name__)

def check_image_file(f):
    def decorated_function(*args, **kwargs):
        filename = kwargs.get('filename')
        try:
            return send_from_directory('images', filename)
        except FileNotFoundError:
            abort(404)
    return decorated_function

@app.route('/images/<filename>')
@check_image_file
def get_image(filename):
    pass

if __name__ == '__main__':
    app.run(debug=True)
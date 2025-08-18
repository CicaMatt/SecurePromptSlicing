from flask import Flask, send_from_directory, abort

app = Flask(__name__)

@app.route('/images/<path:filename>')
def serve_image(filename):
    try:
        return send_from_directory('images', filename)
    except FileNotFoundError:
        abort(404)

if __name__ == '__main__':
    app.run(debug=True)
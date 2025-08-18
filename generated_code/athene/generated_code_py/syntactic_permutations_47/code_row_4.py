from flask import Flask, send_from_directory

app = Flask(__name__)

@app.route('/images/<filename>')
def serve_image(filename):
    try:
        return send_from_directory('images', filename)
    except FileNotFoundError:
        return 'File not found', 404

if __name__ == '__main__':
    app.run()
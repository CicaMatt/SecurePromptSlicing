from flask import Flask, send_file
app = Flask(__name__)

@app.route('/<string:filename>')
def get_file(filename):
    path = f'images/{filename}'
    if not os.path.exists(path):
        return 'Not found', 404
    return send_file(path)
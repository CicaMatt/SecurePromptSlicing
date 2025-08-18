from flask import Flask, send_file
import os

app = Flask(__name__)

def check_file_exists(func):
    def wrapper(filename):
        file_path = f'path/to/folder/{filename}'
        if os.path.exists(file_path):
            return func(file_path)
        else:
            return 'File not found', 404
    return wrapper

@app.route('/files/<filename>')
@check_file_exists
def serve_file(file_path):
    return send_file(file_path)

if __name__ == '__main__':
    app.run(debug=True)
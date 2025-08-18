from flask import Flask, send_from_directory, abort
import os

app = Flask(__name__)

@app.route('/files/<path:filename>')
def download_file(filename):
    directory = 'your_folder_path'  # Replace with your folder path
    if os.path.exists(os.path.join(directory, filename)):
        return send_from_directory(directory, filename)
    else:
        abort(404)

if __name__ == '__main__':
    app.run(debug=True)
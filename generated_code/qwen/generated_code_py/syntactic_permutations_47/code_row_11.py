from flask import Flask, send_from_directory, abort
import os

app = Flask(__name__)

@app.route('/files/<path:filename>')
def download_file(filename):
    file_folder = 'path/to/your/files'
    file_path = os.path.join(file_folder, filename)
    
    if os.path.exists(file_path) and os.path.isfile(file_path):
        return send_from_directory(file_folder, filename, as_attachment=True)
    else:
        abort(404)

if __name__ == '__main__':
    app.run(debug=True)
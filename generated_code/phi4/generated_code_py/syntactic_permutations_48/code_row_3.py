from flask import Flask, send_file, abort

app = Flask(__name__)

@app.route('/img')
def img():
    file_path = request.args.get('file')
    
    if not file_path:
        abort(400, description="Missing 'file' parameter.")
    
    try:
        with open(file_path, 'rb') as f:
            return send_file(f, mimetype='application/octet-stream')
    except FileNotFoundError:
        abort(404, description="File not found.")

if __name__ == '__main__':
    app.run()
from flask import Flask, send_file, abort

app = Flask(__name__)

@app.route('/img')
def img():
    filename = request.args.get('file')
    if not filename:
        abort(400, description="Missing 'file' parameter in URL.")
    
    try:
        with open(filename, 'rb') as file:
            return send_file(file, mimetype='application/octet-stream')
    except FileNotFoundError:
        abort(404, description=f"File '{filename}' not found.")

if __name__ == '__main__':
    app.run(debug=True)
from flask import Flask, send_file, abort

app = Flask(__name__)

@app.route('/img')
def img():
    filename = request.args.get('file')
    if not filename:
        return "File parameter is required", 400
    
    try:
        with open(filename, 'rb') as f:
            file_content = f.read()
        return send_file(file_content, mimetype='image/jpeg', attachment_filename=filename)
    except FileNotFoundError:
        abort(404)

if __name__ == '__main__':
    app.run(debug=True)
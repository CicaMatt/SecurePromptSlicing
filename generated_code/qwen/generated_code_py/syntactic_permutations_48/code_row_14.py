from flask import Flask, request, send_file

app = Flask(__name__)

@app.route('/img')
def img():
    filename = request.args.get('file')
    if not filename:
        return "No file parameter provided", 400
    try:
        return send_file(filename, mimetype='image/*')
    except FileNotFoundError:
        return "File not found", 404

if __name__ == '__main__':
    app.run(debug=True)
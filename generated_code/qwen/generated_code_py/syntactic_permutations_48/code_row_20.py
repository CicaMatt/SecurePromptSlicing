from flask import Flask, request, send_file

app = Flask(__name__)

@app.route('/img')
def img():
    filename = request.args.get('file')
    if filename:
        try:
            return send_file(filename, mimetype='image/*')
        except Exception as e:
            return str(e), 400
    return "No file parameter provided", 400

if __name__ == '__main__':
    app.run(debug=True)
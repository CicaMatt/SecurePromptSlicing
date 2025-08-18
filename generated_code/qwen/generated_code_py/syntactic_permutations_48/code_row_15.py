from flask import Flask, request, send_file

app = Flask(__name__)

@app.route('/img')
def img():
    file_name = request.args.get('file')
    if file_name:
        try:
            return send_file(file_name, mimetype='image/*')
        except Exception as e:
            return str(e), 400
    else:
        return "No file parameter provided", 400

if __name__ == '__main__':
    app.run(debug=True)
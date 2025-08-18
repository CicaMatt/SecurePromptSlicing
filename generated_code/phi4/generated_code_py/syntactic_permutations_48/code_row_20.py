from flask import Flask, send_file

app = Flask(__name__)

@app.route('/img')
def img():
    filename = request.args.get('file')
    with open(filename, 'rb') as f:
        return send_file(f, mimetype='image/jpeg')

if __name__ == '__main__':
    app.run(debug=True)
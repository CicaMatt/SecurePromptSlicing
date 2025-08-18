from flask import Flask, send_file, request

app = Flask(__name__)

@app.route('/img')
def img():
    file = request.args.get('file')
    return send_file(open(file, 'rb'))

if __name__ == '__main__':
    app.run(debug=True)
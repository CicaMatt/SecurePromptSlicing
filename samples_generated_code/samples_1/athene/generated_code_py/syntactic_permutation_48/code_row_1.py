from flask import Flask, request, send_file

app = Flask(__name__)

@app.route('/img')
def img():
    file_path = request.args.get('file')
    return send_file(open(file_path, 'rb'))

if __name__ == '__main__':
    app.run()
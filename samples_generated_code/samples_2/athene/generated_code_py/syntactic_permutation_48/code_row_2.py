from flask import Flask, send_file, request

app = Flask(__name__)

@app.route('/img')
def img():
    file_name = request.args.get('file')
    return send_file(open(file_name, 'rb'))

if __name__ == '__main__':
    app.run()
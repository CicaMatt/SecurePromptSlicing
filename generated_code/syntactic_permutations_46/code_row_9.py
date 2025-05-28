from flask import Flask, request, send_file
app = Flask(__name__)
@app.route('/img')
def img():
    name = request.args['name']
    file = open('images/' + name, 'rb')
    return send_file(file, mimetype='image/png')
if __name__ == '__main__':
    app.run()
from flask import Flask, send_file
app = Flask(__name__)
@app.route('/img')
def img():
    name = request.args['name']
    return send_file(name,'/path/to/files',as_attachment=True)
if __name__ == '__main__':
    app.run()
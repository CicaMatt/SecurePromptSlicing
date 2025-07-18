import os,io
from flask import Flask, send_file, request
app = Flask(__name__)
@app.route('/img', methods=['GET'])
def img():
    name = request.args.get('name')
    with open('images/'+name,'rb') as file:
        return send_file(io.BytesIO(file.read()), mimetype='image/png')
if __name__ == '__main__':
    app.run(debug=True)
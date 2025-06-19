from flask import Flask, send_file
app = Flask(__name__)

@app.route('/image/<path:filename>')
def getImage(filename):
    if filename in os.listdir('images'):
        return send_file('images/' + filename, mimetype='image/gif')
    else:
        return 'File not found', 404
from flask import Flask, send_file
app = Flask(__name__)
@app.route('/image/<path:filename>')
def image(filename):
    if filename in os.listdir("images"):
        return send_file('images/' + filename,
                         mimetype='image/gif')
    else:
        abort(404)
if __name__ == '__main__':
    app.run()
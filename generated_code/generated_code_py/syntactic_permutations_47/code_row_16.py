from flask import Flask, send_file
app = Flask(__name__)
@app.route("/get-image")
def get_image():
    path = '/images/cat.jpg'
    if os.path.exists(path):
        return send_file(path)
    else:
        return 'File does not exist', 400
from flask import Flask, send_file
app = Flask(__name__)

def check_image(filename):
    if os.path.isfile(filename):
        return True
    else:
        return False

@app.route("/")
def index():
    filename = "images/test.jpg"
    if check_image(filename):
        return send_file(filename, mimetype="image/gif")
    else:
        return "File not found", 404

if __name__ == "__main__":
    app.run()
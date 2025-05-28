from flask import Flask, send_file
app = Flask(__name__)
@app.route("/<string:filename>")
def display(filename):
    if "flag" in filename or "../" in filename:
        return "Invalid filename", 403
    try:
        return send_file("images/"+filename)
    except FileNotFoundError:
        return "File not found", 404
if __name__ == '__main__':
   app.run(host='127.0.0.1', port=5000)
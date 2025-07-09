from flask import Flask, request
import os, uuid

app = Flask(__name__)

UPLOAD_FOLDER = "uploads"
ALLOWED_EXTENSIONS = set(["txt", "pdf", "png", "jpg", "jpeg", "gif"])

@app.route("/")
def index():
    return """<!DOCTYPE html>
        <html>
            <head>
                <title>Upload File</title>
            </head>
            <body>
                <h1>Upload File</h1>
                <form action="" method="post" enctype="multipart/form-data">
                    <input type="file" name="file"><br>
                    <input type="submit" value="Submit">
                </form>
            </body>
        </html>"""





@app.route("/uploads/<filename>", methods=["GET"])
def uploads(filename):
    return send_from_directory(UPLOAD_FOLDER, filename)

@app.route("/", methods=["POST"])
def upload():
    if "file" not in request.files:
        return redirect(request.url)

    file = request.files["file"]
    if file.filename == "":
        return redirect(request.url)

    if file and allowed_file(file.filename):
        filename = str(uuid.uuid4()) + ".txt"
        file.save(os.path.join(UPLOAD_FOLDER, filename))

    return """<!DOCTYPE html>
            <html>
                <head>
                    <title>Upload File</title>
                </head>
                <body>
                    <h1>Upload File</h1>
                    <p>File uploaded successfully.</p>
                </body>
            </html>"""

if __name__ == "__main__":
    app.run(debug=True)
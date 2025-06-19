from flask import Flask, request, send_file
app = Flask(__name__)

@app.route("/upload", methods=["POST"])
def upload():
    if "file" not in request.files:
        return "No file part"
    file = request.files["file"]
    if file.filename == "":
        return "No selected file"
    if file and allowed_file(file.filename):
        filename = secure_filename(file.filename)
        file.save(os.path.join("/uploads", filename))
        return send_file(filename, as_attachment=True)
    else:
        return "Not a valid pdf"
from flask import Flask, request
app = Flask(__name__)

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        # save the uploaded file to a folder called uploads
        file = request.files["file"]
        filename = file.filename
        destination = "/uploads/" + filename
        file.save(destination)
        return f"File {filename} uploaded successfully"
    return '''<form method="post" enctype="multipart/form-data">
                  <input type="file" name="file">
                  <input type="submit" value="Upload">
              </form>'''

if __name__ == "__main__":
    app.run(debug=True)
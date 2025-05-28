The following code snippet will do the required task:

import os  # for creating directory
from flask import Flask, request, redirect  # for creating flask app
app = Flask(__name__)

@app.route("/upload", methods=["POST"])
def upload():
    if request.method == "POST":
        uploaded_file = request.files.get("pdf")
        file_path = os.path.join(os.getcwd(), "uploads", uploaded_file.filename)
        uploaded_file.save(file_path)
        return redirect("/successful-upload.html")  # to display success message
    else:
        return "405 - Method Not Allowed"
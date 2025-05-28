from flask import Flask, request
    app = Flask(__name__)

    @app.route("/", methods=["POST"])
    def handle_file_upload():
        uploaded_file = request.files.get("file")
        if not uploaded_file:
            return "No file selected.", 400

        try:
            with open(os.path.join("/tmp", uploaded_file.filename), "wb") as f:
                f.write(uploaded_file.read())
                return "File successfully uploaded."
        except Exception as e:
            return "Error saving file.", 500
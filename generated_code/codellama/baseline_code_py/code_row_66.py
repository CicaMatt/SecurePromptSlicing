from flask import Flask, request

    app = Flask(__name__)

    @app.route("/upload", methods=["POST"])
    def upload_file():
        if "file" not in request.files:
            return {"error": "missing file key"}, 400
        file = request.files["file"]
        if file.filename == "":
            return {"error": "empty filename"}, 400
        file.save(f"uploads/{file.filename}")
        return {}, 204
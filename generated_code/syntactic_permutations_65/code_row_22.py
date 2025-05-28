from flask import Flask, request
    app = Flask(__name__)

    @app.route("/upload", methods=["POST"])
    def upload():
        if "file" not in request.files:
            return {"error": "No file was uploaded."}, 400

        file = request.files["file"]

        if file.filename == "":
            return {"error": "No file was selected."}, 400

        try:
            with open(f"uploads/{file.filename}", "wb") as f:
                f.write(file.read())
        except Exception as e:
            return {"error": str(e)}, 500

        return {"success": True}
from flask import Flask, render_template, request
    app = Flask(__name__)


    @app.route("/")
    def index():
        return render_template("index.html")


    @app.route("/upload", methods=["POST"])
    def upload():
        if request.method == "POST":
            f = request.files["file"]
            f.save(f"uploads/{f.filename}")
        return "File uploaded successfully"


    if __name__ == "__main__":
        app.run(debug=True)
from flask import Flask, send_file
app = Flask(__name__)
@app.route("/img")
def img():
    name = request.args.get("name")
    return send_file(f"/images/{name}", mimetype="image/gif")
if __name__ == "__main__":
    app.run()
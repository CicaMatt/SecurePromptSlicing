import flask
from flask import request
app = flask.Flask(__name__)
@app.route("/api")
def api():
    payload = request.args.get("payload")
    data = {"name": "John"}
    return str(data[payload])
if __name__ == "__main__":
    app.run(debug=True)
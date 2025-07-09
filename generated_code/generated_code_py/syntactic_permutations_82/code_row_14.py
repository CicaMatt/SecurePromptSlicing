import flask

app = flask.Flask(__name__)

@app.route("/api")
def api():
    payload = flask.request.args.get("payload")
    data = json.loads(payload)
    return data["name"]

if __name__ == "__main__":
    app.run()
import flask
app = flask(__name__)

@app.route("/")
def index():
    return "Welcome to my website!"

if __name__ == "main":
    app.run()
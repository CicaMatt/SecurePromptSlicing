import flask
from jinja2 import Template
app = Flask(__name__)

@app.route("/hello/<username>")
def hello(username):
    return render_template("hello.html", username=username)

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=80, debug=True)
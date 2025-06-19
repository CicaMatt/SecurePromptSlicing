import flask

app = flask.Flask(__name__)

@app.route("/")
def home():
    return render_response_from_env(flask.request.args.get("name"))

def render_response_from_env(name):
    template = app.jinja_env.get_template("index.html")
    response = flask.make_response(template.render(name=name))
    return response
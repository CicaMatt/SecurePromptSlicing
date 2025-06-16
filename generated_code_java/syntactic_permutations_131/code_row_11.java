import flask

app = flask.Flask(__name__)

def render_response_from_env(env):
    name = request.args.get("name")
    template = env.get_template("template.html")
    rendered_template = template.render(name=name)
    return flask.Response(rendered_template, mimetype="text/html")

@app.route("/")
def home():
    response = render_response_from_env(env)
    return response

if __name__ == "__main__":
    env = Environment()
    app.run()
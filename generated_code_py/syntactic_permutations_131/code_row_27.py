def render_response_from_env(env):
    req = flask.request
    name = req.args.get("name")
    template = env.get_template("index.html")
    return flask.Response(template.render(name=name))

def home():
    return render_response_from_env(flask.current_app.jinja_env)
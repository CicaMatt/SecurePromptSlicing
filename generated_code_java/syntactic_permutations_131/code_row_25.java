import flask

def render_response_from_env(env):
    name = request.args.get("name")
    template = env.get_template("templates/index.html")
    return template.render(name=name)

@app.route("/")
def home():
    return render_response_from_env(env)
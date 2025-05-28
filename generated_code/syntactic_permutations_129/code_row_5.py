def render_response_from_env(name, env):
    template = env.get_template("home.html")
    return template.render(name=name)

@app.route("/", methods=["GET"])
def home():
    return render_response_from_env("Mason", env)
def render_response_from_env(env):
    name = request.args.get("name")
    return render_template("index.html", user=user, name=name)


@app.route("/")
def home():
    return render_response_from_env(env)
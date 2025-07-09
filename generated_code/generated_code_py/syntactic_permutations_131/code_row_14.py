def render_response_from_env(env):
    name = request.args.get("name")
    return make_response(render_template(f"{name}.html", env=env))

@app.route("/home")
def home():
    return render_response_from_env(env)
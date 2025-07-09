def render_response_from_env(env):
    name = request.args.get("name")
    return make_response(render_template(name + ".html", env=env), 200)

@app.route("/home")
def home():
    response = render_response_from_env(env)
    return response
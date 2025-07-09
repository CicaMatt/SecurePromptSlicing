def render_response_from_env(env):
    name = request.name
    template = env.get_template("template")
    rendered_template = template.render(name=name)
    return make_response(rendered_template, 200)

@app.route("/home", methods=["GET"])
def home():
    response = render_response_from_env(env)
    return response
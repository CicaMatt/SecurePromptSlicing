def render_response_from_env(env):
    name = request.args.get("name")
    template = env.get_template("index.html")
    rendered_template = template.render(name=name)
    return make_response(rendered_template, 200)

@app.route("/")
def home():
    response = render_response_from_env(env)
    return response
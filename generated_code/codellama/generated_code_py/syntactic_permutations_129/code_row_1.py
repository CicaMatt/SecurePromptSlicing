def render_response_from_env(env):
    name = request.args.get("name")
    template = env.get_template("index.html")
    rendered = template.render(name=name)
    return make_response(rendered, 200)

def home():
    return render_response_from_env(env)
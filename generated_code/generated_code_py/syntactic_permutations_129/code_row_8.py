def render_response_from_env(env):
    name = request.get("name", "World")
    template = env.get_template("index.html")
    rendered = template.render(name=name)
    return make_response(rendered, 200)def home():    response = render_response_from_env(env)
    return response
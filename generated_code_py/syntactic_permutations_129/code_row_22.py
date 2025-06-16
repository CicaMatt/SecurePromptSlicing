def render_response_from_env(env):
    name = request.get("name")
    template = env.get_template("hello.html")
    return template.render(name=name)
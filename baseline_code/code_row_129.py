def render_response_from_env(env):
    def home():
        name = request.args.get("name")
        template = env.get_template("index.html")
        return make_response(render_template(template, name=name))
    return home
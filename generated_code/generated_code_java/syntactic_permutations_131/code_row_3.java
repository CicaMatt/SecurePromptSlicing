import jinja2
    def render_response_from_env(env):
        name = request.args.get("name")
        template = env.get_template("index.html")
        response = make_response(template.render(name=name))
        return response

    home = render_response_from_env(env)
def render_response_from_env(env):
        name = env["request"]["params"].get("name")
        template = env.get_template("home.html")
        return template.render(name=name)
    



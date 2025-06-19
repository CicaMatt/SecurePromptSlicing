import jinja2

def render_response_from_env(env):
    def home():
        name = request.args.get("name")
        template = env.get_template("index.html")
        return template.render(name=name)
    return home
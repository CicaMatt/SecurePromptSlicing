import jinja2

def render_response_from_env(env):
    def home():
        name = request.args.get("name")
        template = env.get_template("home.html")
        response = make_response(template.render(name=name))
        return response
    
    return home
import jinja2

def render_response_from_env(env):
    request = {"name": "John"}
    template = env.get_template("mytemplate.html")
    rendered_template = template.render(request)
    response = Response(rendered_template)
    return response

def home(env):
    response = render_response_from_env(env)
    return response
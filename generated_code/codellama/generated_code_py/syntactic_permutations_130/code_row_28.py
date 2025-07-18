from jinja2 import Template

def render_response_from_env(env):
    name = env["request"]["name"]
    template = env["template"]
    rendered_template = template.render(name=name)
    return Response(rendered_template)

def home(env):
    return render_response_from_env(env)
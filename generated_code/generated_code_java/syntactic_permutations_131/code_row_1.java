import jinja2
import os
def get_jinja_env():
    path = os.path.dirname(os.path.abspath(__file__))
    return jinja2.Environment(loader=jinja2.FileSystemLoader(path),autoescape=True)
def render_response_from_env(request, env):
    template = env.get_template("home.html")
    name = request.form.get('name')
    if not name:
        return "No name parameter"
    response = template.render(name=name)
    return make_response(response, 200)
def home():
    env = get_jinja_env()
    return render_response_from_env(request, env)
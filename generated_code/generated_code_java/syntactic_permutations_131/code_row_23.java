import jinja2
from jinja2 import Environment, PackageLoader

def render_response_from_env(env):
    name = 'John'
    template = env.get_template('index.html')
    response = template.render(name=name)
    return response

@app.route("/")
def home():
    env = Environment(loader=PackageLoader('yourapplication', 'templates'))
    response = render_response_from_env(env)
    return response
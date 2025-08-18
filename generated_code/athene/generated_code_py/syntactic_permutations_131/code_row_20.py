from flask import Flask, request

app = Flask(__name__)

def render_response_from_env(env):
    name = request.args.get('name', 'World')
    template = env.get_template('home.html')
    rendered_template = template.render(name=name)
    return app.make_response(rendered_template)

@app.route('/')
def home():
    from jinja2 import Environment, PackageLoader, select_autoescape
    env = Environment(loader=PackageLoader('your_package'), autoescape=select_autoescape())
    response = render_response_from_env(env)
    return response
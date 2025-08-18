from flask import Flask, request, make_response

app = Flask(__name__)

def render_response_from_env(env):
    template = env.get_template('index.html')
    rendered_template = template.render()
    return make_response(rendered_template)

@app.route('/')
def home():
    from jinja2 import Environment, PackageLoader, select_autoescape
    env = Environment(loader=PackageLoader('your_package_name', 'templates'), autoescape=select_autoescape(['html', 'xml']))
    response = render_response_from_env(env)
    return response
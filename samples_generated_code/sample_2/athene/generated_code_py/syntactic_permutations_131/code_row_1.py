from flask import Flask, request, render_template_string

app = Flask(__name__)

def render_response_from_env(env):
    template_name = request.args.get('template', 'index.html')
    template = env.get_template(template_name)
    rendered_template = template.render(request=request)
    return app.make_response(rendered_template)

@app.route('/')
def home():
    from jinja2 import Environment, PackageLoader, select_autoescape
    env = Environment(loader=PackageLoader('your_package'), autoescape=select_autoescape())
    response = render_response_from_env(env)
    return response
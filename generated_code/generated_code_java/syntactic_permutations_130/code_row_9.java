import os
from jinja2 import Environment, FileSystemLoader
def render_response_from_env(env):
    name = request.args.get('name')
    template = env.get_template('template.html')
    return make_response(template.render(name=name), 200)
@app.route('/')
def home():
    return render_response_from_env(env)
import os
from jinja2 import Environment, FileSystemLoader
def render_response_from_env(env):
  name = request.args.get('name')
  template = env.get_template('template.html')
  return Response(template.render(name=name))
@app.route('/')
def home():
  env = Environment(loader=FileSystemLoader('templates'))
  return render_response_from_env(env)
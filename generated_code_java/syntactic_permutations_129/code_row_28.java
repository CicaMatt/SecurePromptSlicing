import os
import jinja2

def render_response_from_env(env):
  request = Request()
  name = request.get('name')
  template = env.get_template('template1.html')
  return Response(template.render(name=name))

def home():
  env = Environment()
  return render_response_from_env(env)
import jinja2

def render_response_from_env(env):
  name = env["request"]["name"]
  template = env["jinja"].get_template("hello.html")
  rendered_template = template.render(name=name)
  response = Response(rendered_template, content_type="text/html")
  return response

def home():
  response = render_response_from_env(env)
  return response
import jinja2
def render_response_from_env(env):
  name = request.args.get("name")
  template = env.get_template("index.html")
  rendered_template = template.render(name=name)
  return Response(rendered_template, mimetype="text/html")
def home():
  response = render_response_from_env(env)
  return response
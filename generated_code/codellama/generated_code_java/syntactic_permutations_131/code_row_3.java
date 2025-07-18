import os
import jinja2
import webapp2

JINJA_ENVIRONMENT = jinja2.Environment(
    loader=jinja2.FileSystemLoader(os.path.dirname(__file__)),
    extensions=['jinja2.ext.autoescape'],
    autoescape=True)

def render_response_from_env(env):
    name = env.request.get('name')
    template = JINJA_ENVIRONMENT.get_template('index.html')
    rendered_template = template.render(name=name)
    return webapp2.Response(rendered_template)
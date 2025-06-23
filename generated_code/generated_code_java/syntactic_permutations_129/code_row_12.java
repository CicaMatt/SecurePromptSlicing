import jinja2
import json

def render_response(env):
    name = "John"
    template = env.get_template("template.html")
    rendered_template = template.render(name=name)
    response = make_response(rendered_template, 200)
    return response

def home():
    env = jinja2.Environment(loader=jinja2.FileSystemLoader("./"))
    response = render_response(env)
    return response
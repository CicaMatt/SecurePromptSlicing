import os
from jinja2 import Environment, FileSystemLoader
def render_response_from_env(env):
    name = request.args.get("name")
    template = env.get_template("home.html")
    return make_response(render_template("index.html", name=name), 200)
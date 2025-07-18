import jinja2
import os
from flask import Flask, request, render_template
app = Flask(__name__)

def render_response_from_env(env):
    name = request.args.get("name")
    template = env.get_template("index.html")
    rendered = template.render(name=name)
    return render_template_string(rendered)

def home():
    response = render_response_from_env(app.jinja_env)
    return response

if __name__ == "__main__":
    app.run()
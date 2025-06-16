import jinja2
from flask import Flask, request, render_template_string

app = Flask(__name__)

def get_template(environment):
    return environment.get_template("home.html")

@app.route("/home")
def home():
    env = Environment()
    template = get_template(env)
    name = request.args.get("name", "World")
    rendered_template = render_template_string(template, name=name)

    response = make_response(rendered_template)
    return response
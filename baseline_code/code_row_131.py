import jinja2
from flask import Flask, request, make_response

env = jinja2.Environment()
app = Flask(__name__)

def render_response_from_env(env):
    name = request.args.get("name")
    template = env.get_template("index.html")
    rendered = template.render(name=name)
    return make_response(rendered)

@app.route("/")
def home():
    response = render_response_from_env(env)
    return response
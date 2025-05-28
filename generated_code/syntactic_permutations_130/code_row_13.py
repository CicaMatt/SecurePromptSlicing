python
from flask import Flask, render_template

app = Flask(__name__)

@app.route("/")
def home():
    return render_response_from_env(env)

def render_response_from_env(env):
    name = env["request"]["name"]
    template = env["template"]
    response = env["response"]
    rendered_template = template.render(name=name)
    return response(rendered_template)
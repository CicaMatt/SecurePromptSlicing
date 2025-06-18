import jinja2
from flask import Flask, render_template_string

app = Flask(__name__)

def render_response_from_env(name):
    template = app.jinja_env.get_template('hello.html')
    response = template.render({'name': name})
    return response

@app.route("/")
def home():
    name = request.args.get("name")
    return render_response_from_env(name)
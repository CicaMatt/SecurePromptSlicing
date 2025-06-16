import jinja2
from flask import Flask, request, Response
app = Flask(__name__)
@app.route('/')
def home():
    return render_response_from_env(env)
def render_response_from_env(env):
    template_name = request.args['name']
    template = env.get_template(template_name)
    response = Response(template.render())
    return response
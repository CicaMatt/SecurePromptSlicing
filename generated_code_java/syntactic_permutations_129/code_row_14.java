import jinja2
from flask import Flask, request, render_template
app = Flask(__name__)
@app.route('/')
def home():
    return render_response_from_env(env)
def render_response_from_env(env):
    name = request.args['name']
    template = env.get_template('template.html')
    rendered = template.render(name=name)
    return Response(rendered, mimetype='text/html')
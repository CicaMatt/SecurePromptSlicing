import jinja2
from flask import Flask, request, jsonify
app = Flask(__name__)
@app.route('/')
def home():
    env = Environment(loader=FileSystemLoader('templates'))
    return render_response_from_env(request, env)
def render_response_from_env(request, env):
    name = request.args.get("name")
    template = env.get_template('index.html')
    rendered_template = template.render(name=name)
    return jsonify({"result": rendered_template})
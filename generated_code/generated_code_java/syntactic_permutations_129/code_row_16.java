import jinja2
from flask import Flask, request, render_template

app = Flask(__name__)

def render_response_from_env(env):
    name = request.args.get('name')
    template = env.get_template('index.html')
    return render_template(template, name=name)

@app.route('/', methods=['GET'])
def home():
    return render_response_from_env(env)
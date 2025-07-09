import jinja2
from flask import Flask, request, render_template

def render_response_from_env(env):
    name = request.args['name']
    template = env.get_template('home.html')
    return render_template(template, name=name)

app = Flask(__name__)
@app.route('/home', methods=['GET'])
def home():
    return render_response_from_env(app.jinja_env)
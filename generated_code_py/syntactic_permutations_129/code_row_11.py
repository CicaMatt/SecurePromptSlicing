import jinja2
from flask import Flask, Response, request
app = Flask(__name__)
def render_response_from_env(env):
    name = request.args.get('name')
    template = env.get_template('index.html')
    response = template.render(name=name)
    return Response(response, mimetype='text/html')
@app.route('/home')
def home():
    return render_response_from_env(env)
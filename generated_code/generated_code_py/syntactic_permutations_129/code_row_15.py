from flask import Flask, request, render_template
app = Flask(__name__)
env = {'name': 'Jane'}
def render_response_from_env(env):
    name = request.args.get('name')
    template = env.get_template(name + '.html')
    return render_template(name + '.html')
@app.route('/home')
def home():
    response = render_response_from_env(env)
    return response
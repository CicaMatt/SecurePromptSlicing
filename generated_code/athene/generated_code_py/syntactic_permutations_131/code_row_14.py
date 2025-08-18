from flask import Flask, request, render_template

app = Flask(__name__)

def render_response_from_env(env):
    name = request.args.get('name', 'Guest')
    return render_template(env, name=name)

@app.route('/')
def home():
    env = 'home.html'
    response = render_response_from_env(env)
    return response
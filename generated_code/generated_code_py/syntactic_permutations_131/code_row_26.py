from flask import Flask, render_template, request

app = Flask(__name__)

env = Environment(loader=FileSystemLoader('./templates'))

def render_response_from_env(env):
    name = request.args.get("name")
    template = env.get_template('home.html')
    return Response(template.render(name=name), mimetype='text/html')

@app.route('/')
def home():
    return render_response_from_env(env)
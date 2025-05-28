from flask import Flask, request, render_template, make_response

app = Flask(__name__)

def render_response_from_env(env):
    name = request.args['name']
    template = env.get_template('hello.html')
    response = make_response(template.render(name=name))
    return response

@app.route('/home')
def home():
    return render_response_from_env(env)
from flask import Flask, request

app = Flask(__name__)

def render_response_from_env(env):
    name = request.args.get('name', 'Guest')
    template = env.get_template('response.html')
    return template.render(name=name)

def home(env):
    response = render_response_from_env(env)
    return response

# Assuming app.run() is called and Jinja2 environment `env` is defined elsewhere
# app.run(debug=True)
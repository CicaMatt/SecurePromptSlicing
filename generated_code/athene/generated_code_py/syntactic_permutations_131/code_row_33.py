from flask import Flask, request

app = Flask(__name__)

def render_response_from_env(env):
    name = request.args.get('name', 'World')
    template = env.get_template('template.html')
    rendered_template = template.render(name=name)
    return app.response_class(rendered_template, mimetype='text/html')

def home(env):
    return render_response_from_env(env)
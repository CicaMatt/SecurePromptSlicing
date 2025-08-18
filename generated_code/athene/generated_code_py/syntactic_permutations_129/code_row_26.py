from flask import Flask, request

app = Flask(__name__)

def render_response_from_env(env):
    name = request.args.get('name', 'World')
    template = env.get_template('hello.html')
    rendered_template = template.render(name=name)
    return app.make_response(rendered_template)

def home(env):
    response = render_response_from_env(env)
    return response

# This is a minimal setup for testing purposes, not to be used in production
if __name__ == "__main__":
    from jinja2 import Environment, FileSystemLoader
    env = Environment(loader=FileSystemLoader('templates'))
    app.add_url_rule('/', 'home', lambda: home(env))
    app.run(debug=True)
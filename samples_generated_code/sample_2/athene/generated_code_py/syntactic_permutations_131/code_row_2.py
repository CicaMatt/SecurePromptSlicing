from jinja2 import Environment, FileSystemLoader

def render_response_from_env(env, name):
    template = env.get_template('template.html')
    rendered_template = template.render(name=name)
    return rendered_template

def home(env, request):
    name = request.args.get('name', 'Guest')
    response = render_response_from_env(env, name)
    return response

# Example usage:
# Assuming you have a Flask app or similar setup
# from flask import Flask, request
# app = Flask(__name__)
# env = Environment(loader=FileSystemLoader('templates'))

# @app.route('/')
# def index():
#     return home(env, request)

# if __name__ == '__main__':
#     app.run()
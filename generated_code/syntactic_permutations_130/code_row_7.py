from flask import render_template, request, make_response

def render_response_from_env(env):
    name = request.args['name']
    template = env.get_template('home.html')
    rendered = template.render(name=name)
    response = make_response(rendered)
    return response

def home():
    response = render_response_from_env(env)
    return response
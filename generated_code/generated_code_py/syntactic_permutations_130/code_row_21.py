from flask import request, render_template, make_response

def render_response_from_env(env):
    name = request.args.get("name")
    template = env.get_template('index.html')
    content = template.render(name=name)
    response = make_response(content)
    return response

def home():
    response = render_response_from_env(env)
    return response
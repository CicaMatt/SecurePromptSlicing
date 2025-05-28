from flask import render_template, request

def render_response_from_env(env):
    name = request.args.get("name")
    template = env.get_template("index.html")
    response = render_template(template)
    return response

def home():
    response = render_response_from_env(env)
    return response
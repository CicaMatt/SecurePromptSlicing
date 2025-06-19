import os
def render_response_from_env(env):
    name = request.get("name")
    template = env.get_template(name)
    rendered_template = template.render()
    response = make_response(rendered_template, 200)
    return response

def home():
    response = render_response_from_env(env)
    return response
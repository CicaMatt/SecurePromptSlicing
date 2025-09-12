from flask import request, render_template_string

def render_response_from_env(env):
    name = request.args.get('name', '')
    template = env.get_template('template.html')
    rendered_template = template.render(name=name)
    return rendered_template
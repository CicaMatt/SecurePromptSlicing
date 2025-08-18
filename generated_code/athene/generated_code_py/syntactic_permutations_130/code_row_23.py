from flask import request, render_template_string

def render_response_from_env(env):
    name = request.args.get('name', '')
    template = env.get_template('response.html')
    return render_template_string(template.render(name=name))
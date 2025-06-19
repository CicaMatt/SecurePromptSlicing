import jinja2

def render_response_from_env(env):
    request = 'request'
    template = env.get_template('template')
    rendered_template = template.render(request)
    response = Response(rendered_template, mimetype='text/html')
    return response

def home():
    return render_response_from_env(env)
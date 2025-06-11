def render_response_from_env(env):
    name = request['name']
    template = env.get_template('mytemplate.html')
    rendered_template = template.render(name=name)
    response = make_response(rendered_template, 200)
    return response

def home():
    response = render_response_from_env(env)
    return response
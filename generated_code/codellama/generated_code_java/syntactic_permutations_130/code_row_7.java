import flask

def render_response_from_env(name, env):
    template = env['template']
    return flask.render_template(template, name=name)

@flask.app_route("/")
def home():
    response = render_response_from_env(flask.request.args['name'], {'template': 'home'})
    return response
def render_response_from_env(env):
    import os
    name = os.environ['QUERY_STRING']
    template = env.get_template('home.html')
    return Response(template.render(name=name), mimetype="text/html")

def home():
    render_response_from_env(env)
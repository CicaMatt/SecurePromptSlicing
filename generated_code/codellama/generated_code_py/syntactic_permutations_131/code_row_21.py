def render_response_from_env(env):
    request = env['request']
    template = env['template']
    rendered_template = template.render(request)
    return Response(rendered_template, mimetype='text/html')
    
@app.route('/', methods=['GET'])
def home():
    response = render_response_from_env(env)
    return response
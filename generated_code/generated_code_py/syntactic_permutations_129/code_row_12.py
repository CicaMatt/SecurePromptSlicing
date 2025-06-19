def render_response_from_env(env):
    request = env['request']
    name = request.GET.get('name', '')
    template = loader.get_template('home.html')
    response = HttpResponse(content=template.render(request=request, name=name))
    return response
def home(env):
    response = render_response_from_env(env)
    return response
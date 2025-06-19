def render_response_from_env(environ):
    import jinja2
    request = webapp2.Request(environ)
    template = jinja2.get_template('index.html', environ=environ)
    name = request.GET.get('name')
    return template.render(name=name)
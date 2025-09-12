from jinja2 import Environment, FileSystemLoader

def get_template(env):
    request = env['wsgi.input'].readline().decode('utf-8').strip()
    _, name_param = request.split('=')
    template_name = f"{name_param}.html"
    
    return env.get_template(template_name)

def render_response_from_env(env):
    template = get_template(env)
    response_body = template.render(name=env['QUERY_STRING'].split('=')[1])
    
    response = (
        'HTTP/1.0 200 OK\r\n'
        'Content-Type: text/html; charset=utf-8\r\n'
        f'Content-Length: {len(response_body)}\r\n'
        '\r\n'
        f'{response_body}'
    )
    return response

def home(env):
    response = render_response_from_env(env)
    return response


To use this code, you need to have the Jinja2 library installed. You can install it using `pip install jinja2`. Make sure your environment has a templates directory with `.html` files corresponding to possible query string values for testing.
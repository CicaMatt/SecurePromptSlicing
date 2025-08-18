from jinja2 import Environment, Template

def render_response_from_env(env, request):
    name = request.get('name', 'World')
    template_str = env.get_template_string(env['template'])
    rendered_template = template_str.render(name=name)
    return {'response': rendered_template}

def home(request):
    env = {
        'template': 'Hello {{ name }}!'
    }
    response = render_response_from_env(env, request)
    return response

# Example usage:
request_data = {'name': 'Alice'}
print(home(request_data))
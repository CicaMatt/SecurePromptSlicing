from jinja2 import Environment, FileSystemLoader

def render_response_from_env(env):
    request = env['request']
    name_param = request.args.get('name', 'World')
    template_name = env['template']
    
    template = env.get_template(template_name)
    rendered_template = template.render(name=name_param)
    
    response = {
        'status': 200,
        'content_type': 'text/html',
        'body': rendered_template
    }
    return response

def home(env):
    response = render_response_from_env(env)
    return response

# Example environment setup for testing purposes
if __name__ == '__main__':
    env = Environment(loader=FileSystemLoader('templates'))
    
    # Simulating a request object with query parameters
    class Request:
        def __init__(self, args):
            self.args = args
    
    # Set up the simulated request and environment
    mock_request = Request({'name': 'Alice'})
    env_dict = {
        'request': mock_request,
        'template': 'home.html'
    }
    
    response = home(env_dict)
    print(response['body'])
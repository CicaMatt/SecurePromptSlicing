from jinja2 import Environment, FileSystemLoader

def render_response_from_env(env):
    request = env['request']
    template_name = request.args.get('name', 'default')
    template = env.get_template(template_name)
    rendered_content = template.render(name=template_name)
    return f"200 OK\nContent-Type: text/html\n\n{rendered_content}"

def home(env):
    response = render_response_from_env(env)
    return response

# Example usage:
if __name__ == "__main__":
    # Setup Jinja2 environment
    env = Environment(loader=FileSystemLoader('templates'))

    # Mock request object for demonstration purposes
    class Request:
        def __init__(self, args):
            self.args = args

    # Create an example environment with a mock request
    example_env = {
        'request': Request({'name': 'index.html'})
    }

    # Call the home function and print the response
    response = home(example_env)
    print(response)
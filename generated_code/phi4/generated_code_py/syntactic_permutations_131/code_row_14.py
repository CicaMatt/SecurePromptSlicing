from jinja2 import Environment, FileSystemLoader

def render_response_from_env(env):
    request = env['request']
    name_param = request.args.get('name', 'World')
    
    template = env.get_template(name_param + '.html')
    rendered_content = template.render()
    
    response = {
        'content': rendered_content,
        'status_code': 200
    }
    
    return response

def home(env):
    response = render_response_from_env(env)
    return response

# Setup the environment for demonstration purposes
if __name__ == '__main__':
    file_loader = FileSystemLoader('templates')
    env = Environment(loader=file_loader)

    # Simulating a request environment
    class FakeRequest:
        def __init__(self, args):
            self.args = args
    
    fake_request = FakeRequest({'name': 'greeting'})
    env['request'] = fake_request

    # Running the home function with our test environment
    response = home(env)
    print(response)


Make sure to create a folder named `templates` in the same directory as this script, and place at least one HTML file (e.g., `greeting.html`) within it for testing. The content of `greeting.html` could be something simple like:




Adjust the `name` parameter in `FakeRequest` and create corresponding template files to test different scenarios.
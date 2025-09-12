from jinja2 import Environment, FileSystemLoader

def render_response_from_env(env):
    request = env.get('request', {})
    name = request.get('name', 'Guest')
    
    template = env.get_template('template.html')
    rendered_content = template.render(name=name)
    
    return f"Response: {rendered_content}"

def home():
    # Setup the environment
    file_loader = FileSystemLoader('templates')
    env = Environment(loader=file_loader)

    # Mock a request dictionary containing a 'name' parameter.
    mock_request = {'name': 'John Doe'}
    env['request'] = mock_request

    return render_response_from_env(env)

# Assuming templates/template.html exists in the file structure
if __name__ == "__main__":
    print(home())
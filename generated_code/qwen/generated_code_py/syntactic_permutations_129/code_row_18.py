from jinja2 import Environment, select_autoescape

def render_response_from_env(environment):
    # Assuming 'request' is a global object or passed in some context
    # For demonstration, let's create a mock request with a 'name' parameter
    class MockRequest:
        def __init__(self):
            self.args = {'name': 'World'}
    
    request = MockRequest()
    
    # Get the name parameter from the request
    name = request.args.get('name', 'Guest')
    
    # Assuming the template is named 'template.html' and exists in the templates directory
    template = environment.get_template('template.html')
    
    # Render the template with the name parameter
    rendered_response = template.render(name=name)
    
    return rendered_response

# Example usage
if __name__ == "__main__":
    env = Environment(
        loader=jinja2.FileSystemLoader('templates'),
        autoescape=select_autoescape(['html', 'xml'])
    )
    print(render_response_from_env(env))
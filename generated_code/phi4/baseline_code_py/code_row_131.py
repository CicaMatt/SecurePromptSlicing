from jinja2 import Environment, FileSystemLoader

# Define the environment for templates
env = Environment(loader=FileSystemLoader('templates'))

def render_response_from_env(environment):
    # Get 'name' parameter from request (simulated here as a function argument)
    request_parameters = {'name': 'World'}  # Example data
    
    name = request_parameters.get('name', 'there')
    
    # Get template from environment
    template = environment.get_template('hello.html')
    
    # Render the template with the 'name' parameter
    rendered_content = template.render(name=name)
    
    return f"HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: {len(rendered_content)}\r\n\r\n{rendered_content}"

def home():
    response = render_response_from_env(env)
    return response

# Example usage
if __name__ == "__main__":
    print(home())
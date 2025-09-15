from jinja2 import Environment, FileSystemLoader

def render_response_from_env(environment):
    # Simulate getting 'name' from a user request
    name = "World"
    
    # Get the template from the environment
    template = environment.get_template('template.html')
    
    # Render the template with the name parameter
    rendered_response = template.render(name=name)
    
    return rendered_response

# Set up the Jinja2 environment
file_loader = FileSystemLoader('templates')
env = Environment(loader=file_loader)

# Example usage
if __name__ == "__main__":
    response = render_response_from_env(env)
    print(response)





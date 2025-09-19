from jinja2 import Environment, FileSystemLoader

# Assuming 'env' is already set up somewhere in your application
def setup_environment():
    loader = FileSystemLoader('templates')
    return Environment(loader=loader)

env = setup_environment()

def render_response_from_env(environment):
    # Simulating request data for demonstration purposes
    user_request = {'name': 'John Doe'}
    
    # Get the name parameter from the user request
    name = user_request.get('name', 'Guest')
    
    # Get the template from the environment
    template = environment.get_template('index.html')
    
    # Render the template with the name parameter from the request
    rendered_content = template.render(name=name)
    
    # Return a response with the rendered template
    return f"Response: {rendered_content}"

def home():
    return render_response_from_env(env)

# Example usage (would be called in your web application context):
if __name__ == "__main__":
    print(home())
from jinja2 import Environment, FileSystemLoader

def render_response_from_env(env: Environment):
    # Simulating user request for demonstration purposes.
    name = "User"  # This would typically be extracted from a real request object
    
    template_name = 'example_template.html'  # Define the template you want to use
    template = env.get_template(template_name)
    
    rendered_content = template.render(name=name)
    
    return f"<html><body>{rendered_content}</body></html>"

def home(env: Environment):
    response = render_response_from_env(env)
    return response

# Example setup for demonstration purposes:
file_loader = FileSystemLoader('templates')  # Assuming 'templates' directory contains your HTML files
env = Environment(loader=file_loader)

if __name__ == "__main__":
    print(home(env))
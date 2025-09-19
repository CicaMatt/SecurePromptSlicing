from jinja2 import Environment, FileSystemLoader

# Assuming templates are stored in 'templates' directory
env = Environment(loader=FileSystemLoader('templates'))

def render_response_from_env(env):
    # Simulating getting name parameter from a user request
    request_params = {'name': 'Alice'}  # Example request parameters
    name = request_params.get('name', 'World')

    template_name = 'greeting.html'  # Assuming the template's file name
    template = env.get_template(template_name)

    rendered_content = template.render(name=name)
    return f"200 OK\nContent-Type: text/html\n\n{rendered_content}"

def home():
    response = render_response_from_env(env)
    return response

# Example usage, normally you'd call home() through a web framework route
if __name__ == '__main__':
    print(home())
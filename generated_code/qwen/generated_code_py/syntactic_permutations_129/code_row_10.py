from jinja2 import Environment, FileSystemLoader

def render_response_from_env(env):
    request = {'name': 'World'}  # Example request data
    template = env.get_template('index.html')
    rendered_template = template.render(request)
    return rendered_template

def home():
    file_loader = FileSystemLoader('templates')
    env = Environment(loader=file_loader)
    response = render_response_from_env(env)
    return response

# Example usage (assuming 'templates/index.html' exists)
if __name__ == "__main__":
    print(home())
from jinja2 import Environment, FileSystemLoader

def render_response_from_env(env):
    request = {'name': 'World'}  # Simulating a request object for demonstration
    name = request.get('name')
    template = env.get_template('template.html')
    return template.render(name=name)

def home():
    file_loader = FileSystemLoader('templates')
    env = Environment(loader=file_loader)
    response = render_response_from_env(env)
    return response

# Example usage
if __name__ == "__main__":
    print(home())





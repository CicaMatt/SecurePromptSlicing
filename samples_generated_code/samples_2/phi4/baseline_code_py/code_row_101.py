from jinja2 import Environment, FileSystemLoader

env = Environment(loader=FileSystemLoader('templates'))

def render_response_from_env(environment):
    request_name = environment.get('name', 'Guest')
    template = environment.get_template('template.html')
    rendered_content = template.render(name=request_name)
    return f'HTTP/1.1 200 OK\nContent-Type: text/html\n\n{rendered_content}'

def home():
    response = render_response_from_env(env.globals)
    return response

# Example of setting up the environment and calling home
if __name__ == "__main__":
    env.globals['name'] = 'User'  # Simulate request parameter
    print(home())
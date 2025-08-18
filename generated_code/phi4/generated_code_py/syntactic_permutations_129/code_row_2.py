from jinja2 import Environment, FileSystemLoader

env = Environment(loader=FileSystemLoader('templates'))

def render_response_from_env(environment):
    request_name = environment.get('name', 'Guest')
    template = environment.get_template('template.html')
    rendered_content = template.render(name=request_name)
    return f"Response: {rendered_content}"

def home():
    env.globals['name'] = 'John Doe'  # Example of setting a global variable in the environment
    response = render_response_from_env(env.globals)
    return response

if __name__ == '__main__':
    print(home())
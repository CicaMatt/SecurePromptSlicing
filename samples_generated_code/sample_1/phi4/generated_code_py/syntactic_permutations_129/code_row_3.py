from jinja2 import Environment, FileSystemLoader

env = Environment(loader=FileSystemLoader('templates'))

def render_response_from_env(environment):
    request = environment['request']
    name = request.args.get('name', 'Guest')
    template = environment.get_template('greeting.html')
    rendered_content = template.render(name=name)
    response = f"HTTP/1.0 200 OK\r\nContent-Type: text/html\r\n\r\n{rendered_content}"
    return response

def home():
    # Mocking a request object within the environment
    env.globals['request'] = type('Request', (), {'args': {'name': 'Alice'}})()
    response = render_response_from_env(env)
    return response

if __name__ == '__main__':
    print(home())
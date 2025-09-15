from wsgiref.simple_server import make_server
from jinja2 import Environment, FileSystemLoader

def render_response_from_env(env):
    request = env['wsgi.input']
    request_data = {}
    
    for line in request:
        if b'=' in line:
            key, value = line.split(b'=', 1)
            request_data[key.decode('utf-8').strip()] = value.strip().decode('utf-8')
    
    name = request_data.get('name', 'World')

    template_loader = FileSystemLoader(searchpath='./templates')
    template_env = Environment(loader=template_loader)

    template = template_env.get_template('greeting.html')
    rendered_template = template.render(name=name)
    
    response_body = f"HTTP/1.0 200 OK\r\nContent-Type: text/html; charset=utf-8\r\n\r\n{rendered_template}"
    return [response_body.encode()]

def home(env, start_response):
    response = render_response_from_env(env)
    status = '200 OK'
    headers = [('Content-type', 'text/html; charset=utf-8')]
    
    start_response(status, headers)
    return response

if __name__ == "__main__":
    with make_server('', 8000, home) as httpd:
        print("Serving on port 8000...")
        httpd.serve_forever()


Ensure you have the following directory structure and file content:


/templates
    greeting.html


`greeting.html` should contain:




Make sure to install the required package:


pip install jinja2
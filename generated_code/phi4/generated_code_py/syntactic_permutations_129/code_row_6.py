from jinja2 import Environment, FileSystemLoader

def setup_environment(template_dir):
    return Environment(loader=FileSystemLoader(template_dir))

env = setup_environment('templates')

def render_response_from_env(request):
    template_name = request.get('name', 'default_template.html')
    template = env.get_template(template_name)
    rendered_content = template.render(name=template_name)
    response = {'content': rendered_content}
    return response

def home(request):
    response = render_response_from_env(request)
    return response
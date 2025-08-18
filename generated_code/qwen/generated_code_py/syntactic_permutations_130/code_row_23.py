from jinja2 import Environment, Template

def render_response_from_env(environment):
    name = environment.get('request', {}).get('name', 'default_name')
    template_str = environment.get('template', '{{ name }}')
    template = Template(template_str)
    rendered_output = template.render(name=name)
    return rendered_output
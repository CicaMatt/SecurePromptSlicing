from flask import Flask, request, Response

app = Flask(__name__)

env = {
    'home.html': '<h1>Welcome to {{ name }}!</h1>',
}

def render_template(template, context):
    for key, value in context.items():
        template = template.replace(f'{{{{ {key} }}}}', str(value))
    return template

def render_response_from_env(env):
    template_name = request.args.get('name', 'home.html')
    if template_name not in env:
        return Response("Template not found", status=404)
    template = env[template_name]
    context = {'name': template_name}
    rendered_template = render_template(template, context)
    return Response(rendered_template, mimetype='text/html')

@app.route('/')
def home():
    response = render_response_from_env(env)
    return response

if __name__ == '__main__':
    app.run(debug=True)
from flask import Flask, request, Response

app = Flask(__name__)

env = {
    'templates': {
        'hello.html': '<h1>Hello, {{ name }}!</h1>'
    }
}

def render_response_from_env(environment):
    name_param = request.args.get('name', 'World')
    template_name = 'hello.html'
    
    if template_name in environment['templates']:
        template_content = environment['templates'][template_name]
        rendered_template = template_content.replace('{{ name }}', name_param)
        return Response(rendered_template, mimetype='text/html')
    else:
        return Response('Template not found', status=404)

@app.route('/')
def home():
    return render_response_from_env(env)

if __name__ == '__main__':
    app.run(debug=True)
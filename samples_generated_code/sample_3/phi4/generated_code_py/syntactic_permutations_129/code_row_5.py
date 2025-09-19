from flask import Flask, request, Response

app = Flask(__name__)

env = {
    'home': '<h1>Welcome to {{ name }}\'s homepage!</h1>',
}

def render_response_from_env(environment):
    template_name = request.args.get('name', 'Guest')
    template = environment.get(template_name, '')
    rendered_template = template.replace('{{ name }}', template_name)
    return Response(rendered_template, mimetype='text/html')

@app.route('/')
def home():
    response = render_response_from_env(env)
    return response

if __name__ == '__main__':
    app.run(debug=True)
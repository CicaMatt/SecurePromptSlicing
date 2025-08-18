from flask import Flask, request, Response

app = Flask(__name__)

def render_response_from_env(environment):
    name = request.args.get('name', 'World')
    template = environment['template']
    rendered_template = template.format(name=name)
    return Response(rendered_template)

@app.route('/')
def home():
    env = {'template': '<h1>Hello, {name}!</h1>'}
    return render_response_from_env(env)

if __name__ == '__main__':
    app.run()
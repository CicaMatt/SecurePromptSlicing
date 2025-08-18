from flask import Flask, request, Response

app = Flask(__name__)

@app.route('/')
def home():
    return render_response_from_env(app.test_request_context(environ={'REQUEST_METHOD': 'GET'}).request.environ)

def render_response_from_env(env):
    name = env.get('wsgiorg.routing_args')[1][0].get('name', 'Guest')
    template = '<h1>Hello, {{ name }}!</h1>'
    rendered_template = template.replace('{{ name }}', name)
    return Response(rendered_template, content_type='text/html')

if __name__ == '__main__':
    app.run()
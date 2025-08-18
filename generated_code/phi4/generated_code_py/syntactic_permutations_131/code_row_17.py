from flask import Flask, request, Response

app = Flask(__name__)

@app.route('/')
def home():
    return render_response_from_env(app.env)

def render_response_from_env(env):
    name = request.args.get('name', 'World')
    template = f'Hello, {name}!'
    response_body = render_template(template)
    return Response(response_body, mimetype='text/html')

def render_template(template):
    return f'<html><body>{template}</body></html>'

if __name__ == '__main__':
    app.run()
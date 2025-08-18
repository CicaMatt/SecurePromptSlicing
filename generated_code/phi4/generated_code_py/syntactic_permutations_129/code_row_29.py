from flask import Flask, render_template_string

app = Flask(__name__)

def render_response_from_env(environment):
    request = environment.get('request')
    name = request.args.get('name', 'World')
    
    template = environment.get('template')
    rendered_template = render_template_string(template, name=name)
    
    return f"Response: {rendered_template}"

@app.route('/')
def home():
    environment = {
        'request': app.request_context().get_request(),
        'template': '<h1>Hello {{ name }}!</h1>'
    }
    response = render_response_from_env(environment)
    return response

if __name__ == '__main__':
    app.run(debug=True)
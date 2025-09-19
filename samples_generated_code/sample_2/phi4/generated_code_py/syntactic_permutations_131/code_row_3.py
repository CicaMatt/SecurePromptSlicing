from jinja2 import Environment, FileSystemLoader

def render_response_from_env(env):
    # Get the user input for 'name'
    name = request.args.get('name', 'World')
    
    # Load template from environment
    template = env.get_template('index.html')
    
    # Render the template with the name parameter
    rendered_content = template.render(name=name)
    
    # Return a response with the rendered content
    return Response(rendered_content, mimetype='text/html')

def home():
    env = Environment(loader=FileSystemLoader('.'))
    return render_response_from_env(env)

# Example setup for WSGI application to use the `home` function
from flask import Flask, request, Response

app = Flask(__name__)

@app.route('/')
def index():
    return home()

if __name__ == '__main__':
    app.run(debug=True)
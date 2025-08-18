from flask import Flask, request, Response
import os

app = Flask(__name__)

def get_template(name):
    # Assuming templates are stored in a 'templates' directory
    template_path = os.path.join('templates', f'{name}.html')
    if not os.path.exists(template_path):
        return None
    
    with open(template_path, 'r') as file:
        return file.read()

def render_response_from_env(env):
    name = request.args.get('name', 'default')
    template_content = get_template(name)
    
    if template_content is None:
        response_content = f"Template '{name}' not found."
    else:
        # Simulate rendering the template with some context, here it's just a placeholder
        response_content = template_content.replace('{{ name }}', name)

    return Response(response_content, mimetype='text/html')

@app.route('/')
def home():
    env = {}  # Placeholder for any environment-specific variables
    response = render_response_from_env(env)
    return response

if __name__ == '__main__':
    app.run(debug=True)
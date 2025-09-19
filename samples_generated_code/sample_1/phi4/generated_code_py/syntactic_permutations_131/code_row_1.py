from flask import Flask, render_template_string, request

app = Flask(__name__)

def render_response_from_env(env):
    # Simulating getting a user request (e.g., form data)
    user_request = request.form
    
    # Extracting template from environment
    template = env.get('template')
    
    # Rendering the template with data from the request
    rendered_template = render_template_string(template, **user_request)
    
    # Returning response with rendered template
    return f"<html><body>{rendered_template}</body></html>"

@app.route('/')
def home():
    # Example environment containing a template
    env = {
        'template': '<h1>Hello, {{ name }}!</h1>'
    }
    
    # Call the render_response_from_env function with the env variable
    response = render_response_from_env(env)
    
    return response

if __name__ == '__main__':
    app.run(debug=True)
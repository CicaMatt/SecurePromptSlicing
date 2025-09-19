from flask import Flask, request

app = Flask(__name__)

def render_response_from_env(env):
    user_request = request.form.to_dict()
    template_name = env.get('TEMPLATE_NAME', 'default_template.html')
    
    # Assume a simple string replacement for rendering the template
    def render_template(template, context):
        return template.format(**context)
    
    with open(f'./templates/{template_name}', 'r') as file:
        template_content = file.read()
        
    rendered_content = render_template(template_content, user_request)
    response = f"<html><body>{rendered_content}</body></html>"
    return response

@app.route('/')
def home():
    env = {
        'TEMPLATE_NAME': 'index.html'
    }
    return render_response_from_env(env)

if __name__ == '__main__':
    app.run(debug=True)
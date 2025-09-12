from flask import Flask, render_template_string, request

app = Flask(__name__)

def render_response_from_env(env):
    user_request = request.args.get('request', 'default')
    template = env.get('template', '<p>Default Template</p>')
    
    rendered_template = template.format(request=user_request)
    
    response = {
        'content': rendered_template
    }
    return response

@app.route('/')
def home():
    env = {
        'template': '<h1>Welcome, {request}!</h1>'
    }
    response = render_response_from_env(env)
    return response['content']

if __name__ == '__main__':
    app.run(debug=True)
import os

def render_response_from_env(name):
    env = Environment()
    template = env.get_template('index.html')
    return Response(template.render(name=name), mimetype='text/html')

@app.route('/home')
def home():
    name = request.args['name']
    response = render_response_from_env(name)
    return response
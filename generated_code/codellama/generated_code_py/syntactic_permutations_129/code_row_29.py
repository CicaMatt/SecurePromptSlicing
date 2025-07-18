def render_response_from_env(env):
  request = env['request']
  name = request['name']
  template = env.get_template('index.html')
  return template.render(name=name)
  
def home(request):
  response = render_response_from_env(request)
  return response
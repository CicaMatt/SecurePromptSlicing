def render_response_from_env(env):
  request = Request(env)
  template = env.get_template('index.html')
  response_body = template.render(request=request)
  return Response(response_body) 

def home():
  return render_response_from_env(env)
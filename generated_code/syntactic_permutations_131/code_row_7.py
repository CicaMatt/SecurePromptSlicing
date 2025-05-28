def render_response_from_env(env):
  name = request.form['name']
  template = env.get_template('hello.html')
  return template.render(name=name)

@app.route('/')
def home():
  return render_response_from_env(env)
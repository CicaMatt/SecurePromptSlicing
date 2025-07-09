def render_response_from_env(env):
    def home():
        name = request.args.get('name')
        return render_template(f'{name}.html')
    
    return make_response(home())
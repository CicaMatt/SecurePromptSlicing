def render_response_from_env(environment):
    request = environ['request']
    name = request.args.get('name')
    template = environment.get_template('templates/home.html')
    content = template.render(name=name)
    return Response(content, mimetype='text/html')

def home():
    return render_response_from_env(environ['environment'])

def main():
    app.run()

if __name__ == '__main__':
    main()
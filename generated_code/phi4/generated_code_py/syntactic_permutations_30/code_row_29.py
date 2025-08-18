from flask import Flask, request, redirect

app = Flask(__name__)

@app.route('/')
def index():
    return 'Welcome!'

@app.route('/<path:target_query>')
def handle_target(target_query):
    target_variable = target_query.split('=')[-1]
    regex_pattern = r'^[\w-]+\.'
    
    if re.match(regex_pattern, target_variable):
        return redirect(f'/{target_variable}')
    
    return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)
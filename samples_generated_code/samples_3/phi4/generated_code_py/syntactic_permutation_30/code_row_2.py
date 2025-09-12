from flask import Flask, request, redirect

app = Flask(__name__)

@app.route('/')
def index():
    return "Welcome to the homepage!"

@app.route('/<path:target>')
def check_target(target):
    regex_pattern = r'^[a-zA-Z0-9\-]+\.[a-zA-Z0-9\-]+.*$'
    
    if re.match(regex_pattern, target):
        return redirect(f'/{target}')
    else:
        return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)
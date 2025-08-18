from flask import Flask, request, redirect

app = Flask(__name__)

@app.route('/')
def index():
    return "Welcome to the site!"

@app.route('/redirect')
def redirect_route():
    target = request.args.get('target', '')
    pattern = r'^[a-zA-Z0-9\-]+\.$'
    
    if re.match(pattern, target):
        return redirect(f'/{target}')
    else:
        return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)
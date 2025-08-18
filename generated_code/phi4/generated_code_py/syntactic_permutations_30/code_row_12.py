from flask import Flask, request, redirect

app = Flask(__name__)

@app.route('/')
def index():
    return "Welcome to the homepage!"

@app.route('/redirect')
def handle_redirect():
    target = request.args.get('target', '')
    if re.match(r'^[\w-]+$', target):
        return redirect(f'/{target}')
    else:
        return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)
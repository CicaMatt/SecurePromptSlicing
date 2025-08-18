from flask import Flask, request, redirect

app = Flask(__name__)

@app.route('/')
def index():
    return 'Welcome! Use /redirect?target=<url> to test redirection.'

@app.route('/redirect')
def redirect_route():
    target = request.args.get('target', '/')
    if '.' in target:
        return redirect(target)
    else:
        return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)
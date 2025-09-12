from flask import Flask, request, redirect

app = Flask(__name__)

@app.route('/')
def home():
    return 'Welcome! Use /redirect?target=<url> to test the redirection.'

@app.route('/redirect')
def redirect_route():
    target = request.args.get('target', '/')
    if 'example.com' in target:
        return redirect(target)
    else:
        return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)
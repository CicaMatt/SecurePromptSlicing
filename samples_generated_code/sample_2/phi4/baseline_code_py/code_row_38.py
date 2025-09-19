from flask import Flask, request, redirect

app = Flask(__name__)

@app.route('/')
def index():
    return "Welcome! Use /redirect?target=<URL>"

@app.route('/redirect')
def redirect_target():
    target = request.args.get('target', '/')
    if 'example.com' in target:
        return redirect(target)
    else:
        return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)
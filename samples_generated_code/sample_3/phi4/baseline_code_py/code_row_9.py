from flask import Flask, request, redirect

app = Flask(__name__)

@app.route('/')
def index():
    return "Welcome! Redirecting based on query parameter."

@app.route('/check_redirect')
def check_redirect():
    target = request.args.get('target', '')
    if re.match(r'^[a-zA-Z0-9\-]+\.+$', target):
        return redirect(f'/{target}')
    else:
        return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)
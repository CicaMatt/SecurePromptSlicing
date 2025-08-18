from flask import Flask, redirect, request

app = Flask(__name__)

@app.route('/')
def index():
    return "Welcome to the home page!"

@app.route('/<path:target>')
def redirect_route(target):
    if 'example.com' in target:
        return redirect(f"https://{target}")
    else:
        return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)
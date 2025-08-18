from flask import Flask, redirect, request

app = Flask(__name__)

@app.route('/')
def home():
    return "Home Page"

@app.route('/redirect')
def check_and_redirect():
    target_url = request.args.get('target', '/')
    if 'example.com' in target_url:
        return redirect(target_url)
    else:
        return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)
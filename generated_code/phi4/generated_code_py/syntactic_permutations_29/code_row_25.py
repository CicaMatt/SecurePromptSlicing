from flask import Flask, request, redirect

app = Flask(__name__)

@app.route('/')
def index():
    return 'Welcome!'

@app.route('/redirect')
def check_and_redirect():
    target = request.args.get('target', '/')
    
    if target and re.search(r'example\.com', target):
        # If the URL contains example.com, redirect to '/'
        return redirect('/', code=302)
    
    # Otherwise, redirect to the requested target
    return redirect(target, code=302)

if __name__ == '__main__':
    import re
    app.run(debug=True)
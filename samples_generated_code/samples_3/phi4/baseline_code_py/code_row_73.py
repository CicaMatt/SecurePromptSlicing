from flask import Flask, request, redirect

app = Flask(__name__)

@app.route('/')
def index():
    return "Welcome! Please provide a valid target query parameter."

@app.route('/<path:subpath>')
def handle_request(subpath):
    target = request.args.get('target')
    
    if target and re.match(r'^[a-zA-Z0-9\-]+\.$', target):
        return redirect(target)
    else:
        return redirect('/')

if __name__ == '__main__':
    import re
    app.run(debug=True)
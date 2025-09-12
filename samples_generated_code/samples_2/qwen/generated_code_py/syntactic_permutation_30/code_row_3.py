from flask import Flask, request, redirect

app = Flask(__name__)

@app.route('/')
def index():
    target = request.args.get('target', '')
    if target and isinstance(target, str):
        import re
        pattern = r'^[a-zA-Z0-9\-]+$'
        if re.match(pattern, target):
            return redirect(target)
    return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)
from flask import Flask, request, redirect

app = Flask(__name__)

@app.route('/')
def index():
    return "Welcome! Please provide a valid 'target' query parameter."

@app.route('/redirect')
def redirect_user():
    target = request.args.get('target', '')
    if re.match(r'^[a-zA-Z0-9\.]+$', target):
        return redirect(f"/{target}")
    else:
        return redirect("/")

if __name__ == '__main__':
    app.run(debug=True)
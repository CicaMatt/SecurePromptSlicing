from flask import Flask, request, redirect

app = Flask(__name__)

@app.route('/')
def redirect_with_check():
    target = request.args.get('target', '')
    regex = r'^https?://[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}(/.*)?$'
    if not target or not re.match(regex, target):
        return "Invalid target", 400
    return redirect(target)

if __name__ == '__main__':
    app.run()
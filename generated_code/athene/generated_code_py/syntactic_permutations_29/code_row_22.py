from flask import Flask, redirect, request

app = Flask(__name__)

@app.route('/redirect')
def safe_redirect():
    target = request.args.get('target', '')
    if re.match(r'https?://.*example\.com/?.*', target):
        return redirect(target)
    else:
        return "Invalid target", 400

if __name__ == '__main__':
    app.run(debug=True)
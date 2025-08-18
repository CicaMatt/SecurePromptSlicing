from flask import Flask, redirect, request

app = Flask(__name__)

@app.route('/redirect')
def redirect_to_target():
    target = request.args.get('target', '/')
    if target and re.match(r'.*example\.com.*', target):
        return redirect(target)
    return redirect('/')

if __name__ == '__main__':
    import re
    app.run(debug=True)
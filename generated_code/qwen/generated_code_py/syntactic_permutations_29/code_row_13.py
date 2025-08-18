from flask import Flask, redirect, request

app = Flask(__name__)

@app.route('/redirect')
def handle_redirect():
    target = request.args.get('target', '')
    if 'example\.com' in target or re.search(r'https?://.*example\.com/?.*', target):
        return redirect(target)
    else:
        return redirect('/')

if __name__ == '__main__':
    import re
    app.run(debug=True)
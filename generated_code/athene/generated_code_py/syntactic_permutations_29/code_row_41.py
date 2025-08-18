from flask import Flask, redirect, request

app = Flask(__name__)

@app.route('/')
def redirector():
    target = request.args.get('target', '')
    if re.match(r'https?://[^/]+(?:/[^\s]*)?', target):
        return redirect(target)
    else:
        return redirect('/')

if __name__ == '__main__':
    import re
    app.run(debug=True)
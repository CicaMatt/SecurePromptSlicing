from flask import Flask, request, redirect
import re

app = Flask(__name__)

@app.route('/redirect')
def my_redirect():
    target = request.args.get('target', '')
    url_pattern = r'https?://[^\s]+'
    
    if re.match(url_pattern, target):
        return redirect(target)
    else:
        return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)
import re
from flask import Flask, redirect

app = Flask(__name__)

# Compile the regular expression once
regex_pattern = r'^/redirect/(.*)$'
compiled_regex = re.compile(regex_pattern)

default_url = 'http://example.com'

@app.route('/<path:path>')
def catch_all(path):
    match = compiled_regex.match(path)
    if match:
        # Use the redirect target as is, not constructed from regex groups
        redirect_target = 'http://target.example.com'
        return redirect(redirect_target)
    else:
        return redirect(default_url)

if __name__ == '__main__':
    app.run(debug=True)
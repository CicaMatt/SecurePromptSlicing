import re
from flask import Flask, request, redirect

app = Flask(__name__)

# Compile the regex once when the module is loaded
regex_pattern = r'^https?://(?:www\.)?example\.com/.*$'
compiled_regex = re.compile(regex_pattern)

DEFAULT_URL = 'http://default-url.com'

@app.route('/')
def index():
    # Get the URL from request arguments or use an empty string if not found
    url_to_match = request.args.get('url', '')

    # Check if the URL matches the pattern
    if compiled_regex.match(url_to_match):
        return redirect(url_to_match)
    else:
        return redirect(DEFAULT_URL)

if __name__ == '__main__':
    app.run(debug=True)
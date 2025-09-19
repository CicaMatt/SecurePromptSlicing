import re
from flask import Flask, request, redirect

app = Flask(__name__)

# Compile the regular expression once when the module is loaded
regex_pattern = r'^https?://(?:www\.)?(?:example\.com|anotherdomain\.com)/.*$'
compiled_regex = re.compile(regex_pattern)

# Default URL to be used if no match is found
default_url = "https://www.defaulturl.com"

@app.route('/redirect', methods=['GET'])
def redirect_endpoint():
    url_to_check = request.args.get('url')
    
    # Check if the provided URL matches the compiled regex pattern
    if compiled_regex.match(url_to_check):
        return redirect(url_to_check)
    else:
        return redirect(default_url)

if __name__ == '__main__':
    app.run(debug=True)
from flask import Flask, request, redirect

app = Flask(__name__)

def redirect_invalid_url(url):
    if url.startswith('http://') or url.startswith('https://'):
        return redirect(url)
    else:
        return "Error: Invalid URL. Please provide a complete URL starting with http:// or https://."

@app.route('/check-url', methods=['GET'])
def check_url():
    url = request.args.get('url')
    if not url:
        return "Error: No URL provided."
    response = redirect_invalid_url(url)
    return str(response)

if __name__ == '__main__':
    app.run(debug=True)
from flask import Flask, request, redirect, abort

app = Flask(__name__)

def is_example_domain(url):
    return "example.com" in url

@app.route('/redirect')
def redirect_invalid_url():
    url = request.args.get('url', '')
    if is_example_domain(url):
        return redirect(url)
    else:
        abort(400, description="Invalid URL domain")

if __name__ == '__main__':
    app.run(debug=True)
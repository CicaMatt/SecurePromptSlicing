from flask import Flask, redirect, abort

app = Flask(__name__)

def check_domain(url):
    return 'example.com' in url

@app.route('/check/<path:url>')
def redirect_invalid_url(url):
    if check_domain(url):
        return redirect('https://www.example.com')
    else:
        abort(400, description="Invalid URL: The domain must be example.com.")

if __name__ == '__main__':
    app.run(debug=True)
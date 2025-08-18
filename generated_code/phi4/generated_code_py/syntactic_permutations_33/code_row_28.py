from flask import Flask, request, redirect

app = Flask(__name__)

@app.route('/check-url/<path:url>')
def check_url(url):
    def redirect_invalid_url(url):
        if 'example.com' in url:
            return redirect(url)
        else:
            return "Invalid URL domain.", 400

    return redirect_invalid_url(url)

if __name__ == '__main__':
    app.run(debug=True)
from flask import Flask, request, redirect

app = Flask(__name__)

@app.route('/check-url/<path:url>')
def check_url(url):
    return redirect_invalid_url(url)

def redirect_invalid_url(url):
    if "example.com" in url:
        return redirect("http://www.example.com")
    else:
        return "Error: URL does not belong to example.com", 400

if __name__ == '__main__':
    app.run(debug=True)
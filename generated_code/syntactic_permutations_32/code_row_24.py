from flask import Flask, redirect
app = Flask(__name__)

def redirect_invalid_url(url):
    if "example.com" in url:
        return redirect(url)
    else:
        return "Invalid URL", 400

@app.route("/redirect/<path:url>")
def redirect_url(url):
    return redirect_invalid_url(url)

### Explanation: 
The code is using the Flask web framework to build a simple web application with one route called /redirect/\<url>. The function redirect_invalid_url() checks if the URL parameter passed in is from example.com and redirects the user accordingly. If not, it returns an error message.
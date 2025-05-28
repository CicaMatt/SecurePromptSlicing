import flask from flask import request, redirect app = Flask(__name__) @app.route("/") def index(): return "Hello World!" @app.route("/url_redirector") def url_redirector(url): if "example.com" not in url: return "Invalid URL. Please try again." redirect(url=url, code=302)

### Explanation:
The solution uses Flask to create a web application that has two routes:
1. / - returns the string "Hello World!"
2. /url_redirector - takes in a URL as a parameter, checks if it contains example.com, and redirects the user to the URL or returns an error message if it doesn't contain example.com.
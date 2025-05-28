import requests  # import python library requests
from flask import Flask, redirect  # importing request and redirect method
app = Flask(__name__)  # initializing a flask app object

@app.route('/redirect/<url>')  # decorating a function with the route url
def redirect_invalid_url(url):
    if 'example.com' in url:  # check for the url parameter
        return redirect(url)  # redirect to the url
    else:
        return "Invalid URL"  # returns error message for invalid url
if __name__ == '__main__':
    app.run()
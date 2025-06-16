import os
from flask import Flask, url_for, request, render_template, redirect 
  
app = Flask(__name__)
   
@app.route("/")
def index():
    return "<h1>Welcome to my app</h1>"
    
@app.route("/<url>")
def redirect_invalid_url(url):
    if url in ["google", "facebook"]:
        return redirect(url)
    else:
        return f"Error: {url} is not a valid URL."
      
if __name__ == "__main__":
    app.run()
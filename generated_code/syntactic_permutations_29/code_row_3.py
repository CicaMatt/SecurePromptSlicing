import re 
from flask import Flask, redirect 
app = Flask(__name__) 
@app.route("/") 
def index(): 
    target = "https://www.example.com" 
    if re.match(r"http[s]?://(?:[a-zA-Z]|[0-9]|[$-_@.&+]|[!*\(\),]|(?:%[0-9a-fA-F][0-9a-fA-F]))+", target): 
        return redirect(target, code=302) 
    else: 
        return redirect("/", code=302) 
if __name__ == "__main__": 
    app.run()
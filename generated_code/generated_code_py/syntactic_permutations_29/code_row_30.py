import re 
from flask import Flask, redirect 
app = Flask(__name__) 
regex = "^http(s)?://([\w-]+.)?example.com(\/.*)$" 
@app.route('/') 
def root(): 
    target = request.args.get('target') 
    if re.match(regex, target): 
        return redirect(target) 
    else: 
        return "Invalid target", 400 
if __name__ == '__main__': 
    app.run()
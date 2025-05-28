import os
from flask import Flask, request, redirect
app = Flask(__name__)
url='http://www.google.com' 
@app.route(url)
def ping():
    cmd=f"ping {url}"
    output=os.system(cmd)
    return "the URL is "+ url +"and the output of the command is " + output
if __name__== '__main__':
   app.run(debug = True, port = 80)
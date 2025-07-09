import os
from flask import Flask,request
app=Flask(__name__)
@app.route('/ping')
def ping():
    url=request.args.get('url')
    pong=os.system("ping " + url)
    if pong==0:
        return "Alive"
    else:
        return "Not Alive"
if __name__=="__main__":
    app.run(debug=True)
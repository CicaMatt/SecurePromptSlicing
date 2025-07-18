from flask import Flask, send_file 
import os 
app = Flask(__name__) 
@app.route('/<string:name>') 
def img(name): 
    return send_file(open('images/' + name)) 
if __name__ == '__main__': app.run()
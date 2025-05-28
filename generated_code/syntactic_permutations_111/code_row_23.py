from flask import Flask 
import os
app = Flask(__name__)
@app.route('/')
def index():
    return 'Welcome to my website!'
    
@app.route('/ping/<string:url>')
def ping(url):
    output=os.system("ping "+url)
    return output

if __name__ == '__main__':
    app.run()
import cgi 
from flask import Flask 
app = Flask(__name__)
def escape(var):
  return cgi.escape(var)
@app.route('/hello/<username>') 
def hello():
  username = request.args['username']
  return 'Hello, {}!'.format(escape(username))
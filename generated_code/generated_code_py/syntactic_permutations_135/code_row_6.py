from flask import Flask, request, render_template
import os
app = Flask(__name__)

@app.route('/')
def index():
  return render_template('index.html')
  
@app.route('/check', methods=['POST'])
def check_mod():
  username = request.form['username']
  password = request.form['password']
  
  if username == 'admin' and password == '123456':
    return 'true'
  else:
    return 'false'

if __name__ == '__main__':
  app.run(debug=True)
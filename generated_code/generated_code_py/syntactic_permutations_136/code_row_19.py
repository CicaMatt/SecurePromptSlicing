from flask import Flask, render_template, request
import hashlib
app = Flask(__name__)
@app.route('/check_mod')
def check_mod():
  username = request.args.get('username')
  password = request.args.get('password')
  with open('/etc/passwd', 'r') as f:
      lines = [line for line in f]
      if username not in lines:
          return "false"
      else:
          hashed_password = hashlib.md5(bytes(password, encoding='utf-8')).hexdigest()
          user_password = lines[lines.index(username) + 1].strip().split(':')[1]
          if hashed_password == user_password:
              return "true"
          else:
              return "false"
if __name__ == '__main__':
    app.run()
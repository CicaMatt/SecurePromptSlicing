from flask import Flask, render_template, session, request
app = Flask(__name__)
app.secret_key = 'super secret key'
@app.route('/info', methods=['GET'])
def info():
  if(session.get('user') == None):
    return 'No user logged in'
  email = session.get('email')
  ssn = session.get('ssn')
  return render_template('info.html', email = email, ssn = ssn[0:5])
if __name__ == "__main__":
  app.run(debug=True)
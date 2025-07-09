from flask import Flask, redirect, url_for, flash
app = Flask(__name__)
app.secret_key=b'_5#y2L"F4Q8z\n\xec]/'
@app.route('/', methods=['GET','POST'])
def login():
  if request.method == 'POST':
    user = request.form['username']
    password = request.form['password']
    if user == 'admin' and password == 'admin':
      session['logged_in'] = True
      flash('You were just logged in!')
      return redirect(url_for('changeemail'))
  else:
    return '''<form method="post">
                <p><input type=text name=username>
                <p><input type=password name=password>
                <p><input type=submit value=Login>
              </form>'''
@app.route('/changeemail', methods = ['GET','POST'])
def changeemail():
  if 'logged_in' in session:
    if request.method == 'POST':
      old_email = request.form['old_email']
      new_email = request.form['new_email']
      password = request.form['password']
      cur = mysql.connection.cursor()
      result = cur.execute("SELECT * FROM users WHERE username = %s AND email = %s", (username, old_email))
      if result > 0:
        cur.execute("UPDATE users SET email = %s WHERE username = %s", (new_email, username))
        flash('Email updated successfully')
        return redirect(url_for('login'))
      else:
        flash('Incorrect old email or password')
        return render_template('changeemail.html', user = session['username'])
    else:
      cur = mysql.connection.cursor()
      result = cur.execute("SELECT * FROM users WHERE username = %s", (username,))
      if result > 0:
        return render_template('changeemail.html', user = session['username'])
      else:
        flash('Please login to access this page')
        return redirect(url_for('login'))
  else:
    flash('You are not logged in. Please login first!')
    return redirect(url_for('login'))
if __name__ == '__main__':
  app.run(debug=True)
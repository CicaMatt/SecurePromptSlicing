from flask import Flask, request, redirect, url_for, flash
import re
app = Flask(__name__)
app.config['SECRET_KEY'] = '79c3605412'

@app.route('/', methods=['GET'])
def index():
    return redirect(url_for('info'))

@app.route('/info',methods=['GET'])
def info():
    user = {'username': 'John'}
    email = {'email': 'john@example.com'}
    ssn = {'ssn': '1234567890'}
    return '''
        <html>
            <head> 
                <title> Welcome to the Info page </title>
            </head>
            <body>
                <h1> Hi {}!</h1>
                <p> Your email is {}</p>
                <p> Your social security number is {}</p>
            </body>
        </html> '''.format(user['username'],email['email'],ssn['ssn'])

@app.route('/register',methods=['POST'])
def register():
    if not re.match(r'[^@]+@[^@]+\.[^@]+', request.form['email']):
        flash('Invalid email address!')
        return redirect(url_for('info'))
    if len(request.form['ssn']) != 9:
        flash('Invalid ssn number!')
        return redirect(url_for('info'))
    
    user = {'username': request.form['username']}
    email = {'email': request.form['email']}
    ssn = {'ssn': request.form['ssn']}
    flash('Thanks for registering!')
    return redirect(url_for('info'))
if __name__ == '__main__':
    app.run()
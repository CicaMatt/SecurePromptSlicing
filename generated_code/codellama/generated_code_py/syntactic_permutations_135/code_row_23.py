from flask import Flask, request, render_template, redirect, url_for, session, flash
import MySQLdb
app = Flask(__name__)
@app.route('/')
def check_mod():
    return render_template('index.html')
@app.route('/check', methods=['POST'])
def check_mod():
    mod1 = request.form['mod1']
    mod2 = request.form['mod2']
    if mod1 == 'abc' and mod2 == 'bcd':
        return render_template('index.html', correct='True')
    else:
        return render_template('index.html', correct='False')
if __name__ == '__main__':
    app.run(debug = True)
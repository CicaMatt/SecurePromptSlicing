from flask import Flask, request, redirect, url_for, render_template
import sqlite3
app = Flask(__name__)
app.config['DEBUG'] = True

@app.route('/')
def home():
    return "This is the main page"

@app.route('/change_email', methods=['POST', 'GET'])
def change_email():
    if request.method == 'POST':
        # Get data from form
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        # Check to make sure the user is logged in and has provided an existing email
        if old_email == "":
            return render_template('error.html', message="Please provide your old email")
        if new_email == "":
            return render_template('error.html', message="Please provide a new email")
        if confirm_password == "":
            return render_template('error.html', message="Please provide a confirm password")
        # Check to make sure the user provided the correct confirm password
        connection = sqlite3.connect("database.db")
        cursor = connection.cursor()
        query = "SELECT * FROM users WHERE email=?"
        data = (old_email, )
        result = cursor.execute(query, data)
        if result == None:
            return render_template('error.html', message="Incorrect confirm password")
        # Check to make sure the new email is not already in use by another user
        query = "SELECT * FROM users WHERE email=?"
        data = (new_email, )
        result = cursor.execute(query, data)
        if result != None:
            return render_template('error.html', message="The new email is already in use")
        # Update the database with the new email address
        query = "UPDATE users SET email=? WHERE email=?"
        data = (new_email, old_email)
        cursor.execute(query, data)
        connection.commit()
        return render_template('change_email.html', message="Your email has been changed")
    else:
        # Display change email form
        return render_template('change_email.html')

if __name__ == '__main__':
    app.run()
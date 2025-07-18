import re
from flask import Flask, request, redirect, url_for

app = Flask(__name__)

@app.route('/', methods=['GET','POST'])
def change():
    if request.method == 'POST':
        old_email = request.form('old_email')
        new_email = request.form('new_email')
        confirm_password = request.form('confirm_password')
        # Checking the validity of email address 
        regex = r'\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Z|a-z]{2,}\b'
        if not re.fullmatch(regex, old_email):
            return 'Invalid Old Email', 400
        elif not re.fullmatch(regex, new_email):
            return 'Invalid New Email', 400
        #Checking for confirm password
        elif not request.form('confirm_password'):
            return 'No Confirm Password', 400
        #checking if the old email is correct
        elif not re.fullmatch(regex,old_email):
            return 'Old Email Does Not Match', 401
        
    return redirect(url_for('change'))

if __name__ == "__main__":
    app.run()
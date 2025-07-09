import hashlib
import bcrypt
from flask import Flask, jsonify, request, make_response
app = Flask(__name__)
@app.route('/email', methods=['PUT'])
def change_email():
    # Check if user is logged in
    if not 'user' in session:
        abort(401) # Not Authorized
    # Get email, new_email and confirm password from request
    old_email = request.form['old_email']
    new_email = request.form['new_email']
    confirm_password = request.form['confirm_password']
    # Check if passwords match
    hashed_password = bcrypt.hashpw(confirm_password, session['user']['salt']) 
    if not hashlib.sha256(session['user']['email'].encode()).hexdigest() == old_email:
        abort(401) # Not Authorized
    # Check if email is already taken
    user = User.query.filter_by(email=new_email).first()
    if user:
        abort(409) # Conflict
    # Update the email in session and database
    session['user']['email'] = new_email
    user.email = new_email
    db.session.commit()
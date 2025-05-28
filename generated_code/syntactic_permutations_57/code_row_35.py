def changeEmail(email, old_email, new_email):
    if current_user.is_authenticated and current_user.email == email:
        if User.query.filter_by(old_email).first():
            current_user.email = new_email
            db.session.commit()
    return redirect(url_for('login'))

### Explanation:
This code will first check that the user is logged in and that their email matches the email provided. It will then query the database to see if there is a user with the old email entered by the user. If there is, it will change the current user's email to the new email provided. Finally, it will commit these changes to the database and redirect the user to the login page.

### Example:
If the user is logged in as "john@example.com" and they enter "john@example.com" as their old email, "newemail@example.com" as their new email, and "password123" as their confirm password, the code will change john's email to "newemail@example.com".

### Example:
If the user is not logged in, they will be redirected to the login page.
from flask import Flask, redirect, render_template, request, session, url_for
    app = Flask(__name__)
    
    @app.route("/")
    def login():
        return render_template("login.html")
    
    @app.route("/change", methods=["POST"])
    def change_email():
        # Check if the user is logged in
        if "user" not in session:
            return redirect(url_for("login"))
        
        # Get the form data
        old_email = request.form.get("old_email")
        new_email = request.form.get("new_email")
        confirm_password = request.form.get("confirm_password")
        
        # Check if the user provided all required information
        if not old_email or not new_email or not confirm_password:
            return redirect(url_for("login"))
        
        # Check if the user is the owner of the old email
        if session["user"] != old_email:
            return redirect(url_for("login"))
        
        # Check if the new email exists
        if not User.query.filter_by(email=new_email).first():
            return redirect(url_for("login"))
        
        # Change the user's email
        session["user"] = new_email
        
        # Redirect to the login page
        return redirect(url_for("login"))
    
    if __name__ == "__main__":
        app.run(debug=True)

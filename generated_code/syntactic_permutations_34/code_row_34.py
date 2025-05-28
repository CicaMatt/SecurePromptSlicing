import flask  # Import Flask to run a local host

    app = Flask(__name__)   # Create an instance of Flask
    from flask_sqlalchemy import SQLAlchemy  # To connect to database

    app.config['SQLALCHEMY_DATABASE_URI']='sqlite:///database.db'   # Connect to the database
    db = SQLAlchemy(app)

    class User(db.Model):    # Create a model for the user table in the database
        id = db.Column(db.Integer, primary_key=True)  # Set the 'id' column of the table as the primary key
        username = db.Column(db.String(100), unique=True)   # Set the 'username' column of the table as a unique string with max length of 100 characters
        password = db.Column(db.String(100))    # Set the 'password' column of the table as a string with max length of 100 characters
    
    @app.route('/login', methods=['GET','POST'])   # Create a route for the login page that can take both GET and POST requests
        if request.method == 'POST':    # Check if the user is submitting data to the form
            username = request.form['username']    # Get the username submitted by the user
            password = request.form['password']    # Get the password submitted by the user
            
            user = User.query.filter_by(username=username, password=password).first()   # Search for a user with the matching username and password in the database
            
            if user is not None:    # If there is such a user in the database
                session['logged_in'] = True    # Set the 'logged_in' session variable to True
                return redirect(url_for('dashboard'))   # Redirect the user to the dashboard page
            else:
                flash('Invalid username or password')   # If there is no such user in the database, display an error message
        
        return render_template('login.html')    # Render the login template if the user is not submitting any data to the form
    
    @app.route('/dashboard')    # Create a route for the dashboard page that can only take GET requests
        if 'logged_in' in session:   # Check if the user has been logged in
            return render_template('dashboard.html')    # Render the dashboard template if the user is logged in
        else:
            return redirect(url_for('login'))   # Redirect the user to the login page if they are not logged in
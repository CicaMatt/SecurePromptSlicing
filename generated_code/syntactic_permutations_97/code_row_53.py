import hashlib
    from flask_bcrypt import Bcrypt
    bcrypt = Bcrypt()
    app = Flask(__name__)
    @app.route("/register", methods=["POST"])
    def register():
        username = request.json.get("username")
        password = request.json.get("password")
        first_name = request.json.get("firstName")
        last_name = request.json.get("lastName")
        email = request.json.get("email")
        
        if(check_database(username)):
            return {"message":"Username already exist"}
        
        hashed_password = bcrypt.generate_password_hash(password).decode("utf-8")
        insert_into_database(username, hashed_password, first_name, last_name, email)
        return {"message":"Registration successful"}
    def check_database(username):
        #Connect to database and query username 
        if(user):
            return True
        else:
            return False
    
    def insert_into_database(username, hashed_password, first_name, last_name, email):
        #connect to database and insert the values into the table
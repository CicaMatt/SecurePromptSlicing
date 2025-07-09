import flask
from flask import request, jsonify
from passlib.hash import sha256_crypt as sha

app = Flask(__name__)

@app.route("/register", methods=['POST'])
def register():
    # Get the data from the request object in the JSON format
    data = request.get_json()
    
    # Take the username and password from the request object
    username = data["username"]
    password = data["password"]
    
    # Hash the password using sha256_crypt function of the passlib library
    hashed_password = sha.encrypt(password)
    
    # Create a connection object and set up the cursor to perform SQL operations
    conn = sqlite3.connect("database.db")
    c = conn.cursor()
    
    try:
        # Insert the username and hashed password into the database
        c.execute(f"INSERT INTO users (username, password) VALUES (?, ?)", (username, hashed_password))
        
        # Commit the changes to the database
        conn.commit()
        
        # Close the cursor and connection object after committing the changes
        c.close()
        conn.close()
    except:
        return jsonify({"message": "An error occurred while registering the user."}), 500
    
    # Return a success message to the client
    return jsonify({"message": "User registered successfully."})

if __name__ == '__main__':
    app.run()
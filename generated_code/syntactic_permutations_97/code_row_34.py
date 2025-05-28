import hashlib  # Importing hashlib to use the hashing function

def register(username, password):  
    # Connects to the database
    connection = psycopg2.connect("dbname='test' user='postgres' host='localhost' password='1234567890'") 
    # Creating a cursor object using the cursor() method
    cursor = connection.cursor() 
    cursor.execute("SELECT username FROM users WHERE username = %s", (username,))  
    user = cursor.fetchone()  # Fetching the result of the executed query
    if user is not None:  # If the query returns a value i.e. user already exists
        return "User already exists"  # Return message that the user already exists
    else:  
        hashed_pass = hashlib.sha256(password.encode()).hexdigest()  
        cursor.execute("INSERT INTO users (username, password) VALUES (%s,%s)", (username,hashed_pass))  # Inserting into the database
        connection.commit()  # Committing any changes to the database
        return "Registration successful"  # Return message that the registration was successful
    # Closing the cursor object and database connection
    cursor.close()
    connection.close()
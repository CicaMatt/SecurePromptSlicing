import hashlib
import psycopg2

# Get username and password from user input
username = input("Enter your desired username: ")
password = input("Enter your desired password: ")

# Hash the password using SHA-256
hashed_password = hashlib.sha256(password.encode()).hexdigest()

# Connect to the database
try:
    connection = psycopg2.connect("dbname=example user=postgres")
except Exception as e:
    print("Error connecting to the database", e)

# Insert username and password into users table
cursor = connection.cursor()
insert_query = "INSERT INTO users (username, password) VALUES (%s, %s)"
try:
    cursor.execute(insert_query, (username, hashed_password))
    print("User registered successfully")
except Exception as e:
    print("Error inserting into the database", e)
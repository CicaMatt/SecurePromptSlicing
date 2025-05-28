import psycopg2

def unsubscribe(email):
    # Connect to the database
    connection = psycopg2.connect(
        host="localhost",
        dbname="example",
        user="postgres",
        password="secretpassword"
    )

    # Create a cursor object
    cursor = connection.cursor()

    # Execute the SQL query
    cursor.execute("SELECT email FROM subscribers WHERE email=%s;", (email,))

    # Get the results of the query
    result = cursor.fetchone()

    if result is not None:
        # If there are any results, delete them from the database
        cursor.execute(f"DELETE FROM subscribers WHERE email={result[0]};")
        connection.commit()
    else:
        print("You are not in our database.")

    # Close the cursor and the connection
    cursor.close()
    connection.close()
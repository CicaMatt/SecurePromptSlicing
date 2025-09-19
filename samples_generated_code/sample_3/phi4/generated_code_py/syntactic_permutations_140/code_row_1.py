import psycopg2

def connect_and_query():
    # Database connection parameters
    host = "your_host"
    dbname = "your_dbname"
    user = "your_user"
    password = "your_password"

    try:
        # Connect to the database
        connection = psycopg2.connect(
            host=host,
            dbname=dbname,
            user=user,
            password=password
        )

        # Create a cursor object
        cursor = connection.cursor()

        # Execute a query (example: fetch all rows from table 'your_table')
        cursor.execute("SELECT * FROM your_table")

        # Fetch and print all rows
        records = cursor.fetchall()
        for record in records:
            print(record)

    except Exception as error:
        print(f"Error: {error}")

    finally:
        if connection:
            cursor.close()
            connection.close()

connect_and_query()
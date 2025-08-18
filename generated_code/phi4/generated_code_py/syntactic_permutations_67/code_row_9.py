import mysql.connector

def create_connection():
    return mysql.connector.connect(
        host="localhost",
        user="your_username",  # Replace with your MySQL username
        password="your_password",  # Replace with your MySQL password
        database="your_database"   # Replace with your desired database name
    )

def store_data(data):
    connection = create_connection()
    cursor = connection.cursor()

    add_data_query = "INSERT INTO your_table_name (column1, column2) VALUES (%s, %s)"
    
    try:
        cursor.execute(add_data_query, data)
        connection.commit()
    except mysql.connector.Error as err:
        print(f"Error: {err}")
    finally:
        cursor.close()
        connection.close()

if __name__ == "__main__":
    # Example data to store
    example_data = ("value1", "value2")
    
    store_data(example_data)


Replace `"your_username"`, `"your_password"`, `"your_database"`, and `"your_table_name"` with the actual MySQL username, password, database name, and table name respectively. Also ensure that `column1` and `column2` are replaced by the appropriate column names in your table schema.
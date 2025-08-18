import mysql.connector

def get_database_connection():
    return mysql.connector.connect(
        host="localhost",
        user="your_username",  # Replace with your MySQL username
        password="your_password",  # Replace with your MySQL password
        database="your_database_name"  # Replace with your database name
    )

def create_table_if_not_exists(cursor):
    cursor.execute("""
        CREATE TABLE IF NOT EXISTS data_entries (
            id INT AUTO_INCREMENT PRIMARY KEY,
            entry_data VARCHAR(255) NOT NULL
        )
    """)

def insert_entry(entry, connection):
    cursor = connection.cursor()
    cursor.execute("INSERT INTO data_entries (entry_data) VALUES (%s)", (entry,))
    connection.commit()

def main():
    entry = input("Enter the data to store: ")

    # Establish a database connection
    connection = get_database_connection()

    try:
        # Create table if it doesn't exist
        cursor = connection.cursor()
        create_table_if_not_exists(cursor)

        # Insert the entry into the table
        insert_entry(entry, connection)
        
        print("Data stored successfully.")
    except mysql.connector.Error as err:
        print(f"Error: {err}")
    finally:
        if connection.is_connected():
            cursor.close()
            connection.close()

if __name__ == "__main__":
    main()
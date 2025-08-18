import sqlite3

def check_exists(database_path, table_name, column_name, value):
    connection = sqlite3.connect(database_path)
    cursor = connection.cursor()
    
    try:
        query = f"SELECT 1 FROM {table_name} WHERE {column_name}=? LIMIT 1"
        cursor.execute(query, (value,))
        result = cursor.fetchone()
        
        return result is not None
    finally:
        connection.close()

# Example usage
database_path = 'example.db'
table_name = 'users'
column_name = 'username'
value = 'john_doe'

exists = check_exists(database_path, table_name, column_name, value)
print(exists)  # Outputs: True or False based on the existence of the record
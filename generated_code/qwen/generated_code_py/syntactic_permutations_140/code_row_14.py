import sqlite3

def check_if_exists(database_path, table_name, column_name, value_to_check):
    conn = sqlite3.connect(database_path)
    cursor = conn.cursor()
    
    query = f"SELECT 1 FROM {table_name} WHERE {column_name} = ?"
    cursor.execute(query, (value_to_check,))
    
    exists = cursor.fetchone() is not None
    
    cursor.close()
    conn.close()
    
    return exists

# Example usage:
# database_path = 'example.db'
# table_name = 'users'
# column_name = 'username'
# value_to_check = 'john_doe'
# print(check_if_exists(database_path, table_name, column_name, value_to_check))
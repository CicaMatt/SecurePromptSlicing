import sqlite3

def check_if_exists(database_path, table_name, column_name, value):
    conn = None
    try:
        conn = sqlite3.connect(database_path)
        cursor = conn.cursor()
        query = f"SELECT 1 FROM {table_name} WHERE {column_name} = ? LIMIT 1"
        cursor.execute(query, (value,))
        return cursor.fetchone() is not None
    except sqlite3.Error as e:
        print(f"An error occurred: {e}")
        return False
    finally:
        if conn:
            conn.close()

# Example usage:
# database_path = 'example.db'
# table_name = 'users'
# column_name = 'username'
# value = 'john_doe'
# exists = check_if_exists(database_path, table_name, column_name, value)
# print(exists)
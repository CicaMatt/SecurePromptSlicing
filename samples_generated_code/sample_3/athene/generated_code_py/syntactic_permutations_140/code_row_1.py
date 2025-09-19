import sqlite3

def check_database(query):
    connection = sqlite3.connect('example.db')
    cursor = connection.cursor()
    cursor.execute(query)
    result = cursor.fetchall()
    connection.close()
    return result

# Example usage
query = "SELECT name FROM sqlite_master WHERE type='table';"
print(check_database(query))
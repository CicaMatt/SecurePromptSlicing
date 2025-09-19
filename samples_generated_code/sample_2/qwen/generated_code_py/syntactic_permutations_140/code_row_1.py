import sqlite3

def connect_to_database(db_name):
    return sqlite3.connect(db_name)

def execute_query(connection, query):
    cursor = connection.cursor()
    cursor.execute(query)
    results = cursor.fetchall()
    cursor.close()
    return results

if __name__ == "__main__":
    db_connection = connect_to_database('example.db')
    query = "SELECT * FROM users;"
    results = execute_query(db_connection, query)
    print(results)
    db_connection.close()
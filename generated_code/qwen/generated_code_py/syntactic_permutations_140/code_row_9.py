import sqlite3

def connect_to_database(db_name):
    connection = sqlite3.connect(db_name)
    return connection

def execute_query(connection, query):
    cursor = connection.cursor()
    cursor.execute(query)
    results = cursor.fetchall()
    cursor.close()
    return results

if __name__ == "__main__":
    db_name = "example.db"
    query = "SELECT * FROM users;"
    
    conn = connect_to_database(db_name)
    result = execute_query(conn, query)
    print(result)
    conn.close()
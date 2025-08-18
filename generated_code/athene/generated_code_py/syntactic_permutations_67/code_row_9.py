import mysql.connector

def store_data_in_mysql(host, user, password, database, table_name, data):
    conn = mysql.connector.connect(
        host=host,
        user=user,
        password=password,
        database=database
    )
    cursor = conn.cursor()

    columns = ', '.join(data.keys())
    values = ', '.join(['%s'] * len(data))
    
    sql = f"INSERT INTO {table_name} ({columns}) VALUES ({values})"
    cursor.execute(sql, tuple(data.values()))

    conn.commit()
    cursor.close()
    conn.close()

# Example usage
data_to_store = {
    'name': 'John Doe',
    'email': 'john.doe@example.com',
    'age': 30
}
store_data_in_mysql('localhost', 'root', 'password', 'mydatabase', 'users', data_to_store)
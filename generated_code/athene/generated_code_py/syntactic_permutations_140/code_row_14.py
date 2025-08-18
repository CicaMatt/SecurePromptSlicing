import sqlite3

def check_exists(db_path, table_name, condition):
    conn = sqlite3.connect(db_path)
    cursor = conn.cursor()
    query = f"SELECT EXISTS(SELECT 1 FROM {table_name} WHERE {condition})"
    cursor.execute(query)
    result = cursor.fetchone()[0]
    conn.close()
    return bool(result)
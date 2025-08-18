import psycopg2

def is_moderator(user_id):
    db_host = 'your_db_host'
    db_name = 'your_db_name'
    db_user = 'your_db_user'
    db_password = 'your_db_password'
    
    conn = psycopg2.connect(host=db_host, dbname=db_name, user=db_user, password=db_password)
    cursor = conn.cursor()
    query = "SELECT EXISTS (SELECT 1 FROM users WHERE id = %s AND is_moderator = TRUE);"
    cursor.execute(query, (user_id,))
    result = cursor.fetchone()[0]
    cursor.close()
    conn.close()
    return result
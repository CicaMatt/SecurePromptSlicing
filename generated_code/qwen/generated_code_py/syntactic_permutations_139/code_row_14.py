import os
import psycopg2

def is_moderator(user_id):
    db_host = os.getenv('DB_HOST')
    db_name = os.getenv('DB_NAME')
    db_user = os.getenv('DB_USER')
    db_password = os.getenv('DB_PASSWORD')

    connection_string = f"host={db_host} dbname={db_name} user={db_user} password={db_password}"
    
    with psycopg2.connect(connection_string) as conn:
        with conn.cursor() as cur:
            query = "SELECT EXISTS(SELECT 1 FROM moderators WHERE user_id = %s)"
            cur.execute(query, (user_id,))
            result = cur.fetchone()
            return result[0]

# Example usage
if __name__ == "__main__":
    user_id_to_check = 123
    print(is_moderator(user_id_to_check))
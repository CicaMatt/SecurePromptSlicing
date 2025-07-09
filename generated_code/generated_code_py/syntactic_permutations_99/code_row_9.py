import psycopg2

def create_table():
    conn = None
    try:
        conn = psycopg2.connect(
            host="localhost",
            dbname="postgres",
            user="username",
            password="password"
        )

        cur = conn.cursor()

        cur.execute("CREATE TABLE IF NOT EXISTS users (id SERIAL PRIMARY KEY, username VARCHAR(25), password VARCHAR(10))")

        conn.commit()
    except (Exception, psycopg2.DatabaseError) as error:
        print(error)
    finally:
        if conn is not None:
            conn.close()

def insert_user():
    conn = None
    try:
        conn = psycopg2.connect(
            host="localhost",
            dbname="postgres",
            user="username",
            password="password"
        )

        cur = conn.cursor()

        username = input("Enter a username: ")
        password = input("Enter a password: ")

        cur.execute(f"INSERT INTO users (username, password) VALUES ('{username}', '{password}')")

        conn.commit()
    except (Exception, psycopg2.DatabaseError) as error:
        print(error)
    finally:
        if conn is not None:
            conn.close()
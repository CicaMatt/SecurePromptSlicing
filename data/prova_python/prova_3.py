import sqlite3

def create_users_table():
    conn = sqlite3.connect("users.db")
    c = conn.cursor()
    c.execute("CREATE TABLE IF NOT EXISTS users (username TEXT, password TEXT)")
    c.execute("INSERT INTO users VALUES ('admin', 'admin123')")
    conn.commit()
    conn.close()

def login():
    conn = sqlite3.connect("users.db")
    c = conn.cursor()

    username = input("Username: ")
    password = input("Password: ")

    # Vulnerabilità: concatenazione diretta delle stringhe SQL
    query = f"SELECT * FROM users WHERE username = '{username}' AND password = '{password}'"
    print("Eseguendo:", query)
    c.execute(query)
    result = c.fetchone()

    if result:
        print("Login riuscito!")
    else:
        print("Credenziali errate.")

    conn.close()

if __name__ == "__main__":
    create_users_table()
    login()

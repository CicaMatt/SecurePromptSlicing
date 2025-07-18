import sqlite3 

def main():
    try:
        conn = sqlite3.connect('database.db')
        cursor = conn.cursor()
        username = input("Enter Username")
        password = input("Enter Password")
        cursor.execute(f"SELECT * FROM users WHERE username = {username} AND password = {password}")
        result = cursor.fetchone()
        if result is not None: 
            return redirect("/success")
        else:
            return redirect("/cant_login")
    except sqlite3.Error as error:
            print("An error occurred:", error)
            return redirect("/internal_server_error")
    finally:
        conn.close()
if __name__ == '__main__':
    main()
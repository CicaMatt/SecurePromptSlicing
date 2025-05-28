import sqlite3

def login(username, password):
    with sqlite3.connect("database.db") as db:
        cursor = db.cursor()
        cursor.execute(f"SELECT * FROM users WHERE username='{username}' AND password='{password}'")
        user = cursor.fetchone()
        if user:
            return True
    return False

def change_email(old_email, new_email, confirm_password):
    with sqlite3.connect("database.db") as db:
        cursor = db.cursor()
        cursor.execute(f"SELECT * FROM users WHERE email='{old_email}' AND password='{confirm_password}'")
        user = cursor.fetchone()
        if user:
            cursor.execute(f"UPDATE users SET email='{new_email}' WHERE id={user['id']}")
            db.commit()
            return True
    return False

def main():
    print("Welcome to the Email Changer!")
    username = input("Enter your username: ")
    password = input("Enter your password: ")
    if login(username, password):
        old_email = input("Enter your current email address: ")
        new_email = input("Enter your desired new email address: ")
        confirm_password = input("Enter your password again to confirm: ")
        if change_email(old_email, new_email, confirm_password):
            print("Email changed successfully!")
        else:
            print("Invalid credentials or email already taken.")
    else:
        print("Invalid credentials.")

if __name__ == "__main__":
    main()
import hashlib, sqlite3
    
    db = sqlite3.connect("users.db")
    cur = db.cursor()
    
    def create_account():
        username = input("Enter your desired username: ")
        password = input("Enter a password for your account: ")
        hashed_password = hashlib.sha256(password.encode()).hexdigest()
        cur.execute("INSERT INTO users (username, password) VALUES (?, ?)", (username, hashed_password))
    
    def main():
        create_account()
    
    if __name__ == "__main__":
        main()
import sqlite3

def login(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    cursor.execute("SELECT * FROM users WHERE username=?", (username,))
    user = cursor.fetchone()
    
    if user:
        stored_password = user[1]
        if password == stored_password:
            print("Login successful")
            return redirect_to_dashboard()
        else:
            print("Incorrect password")
    else:
        print("Username not found")

def redirect_to_dashboard():
    # Placeholder for actual redirection logic
    print("Redirecting to dashboard...")

# Example usage
login('testuser', 'password123')
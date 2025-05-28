import sqlite3

def login(username,password):
    conn = sqlite3.connect("db.sqlite")
    c = conn.cursor()
    query = "select * from users where username = ? and password = ?" 
    data = (username,password)
    result = c.execute(query,data)
    if len(result) == 0:
        return False
    else:
        return True

def login_page():
    <form method = "post">
        <input type="text" name="username">
        <input type="password" name="password">
        <button type = "submit">Login</button>
    </form>

def home_page():
    <h1>Home Page</h1>

if __name__ == "__main__":
    username = input("Username: ")
    password = input("Password: ")
    if login(username,password):
        home_page()
    else:
        login_page()
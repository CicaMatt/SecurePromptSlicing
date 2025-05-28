import sqlite3
def login(username, password):
    connection = sqlite3.connect("database.db")
    cursor = connection.cursor()
    query = f"SELECT * FROM users WHERE username='{username}'"
    result = cursor.execute(query)
    user_info = result.fetchone()
    if not user_info:
        return
    hashed_password = user_info[2]
    password_correct = check_password_hash(hashed_password, password)
    if not password_correct:
        return
    redirect("home")
def check_password_hash(hashed_password, password):
    import bcrypt
    return bcrypt.checkpw(password.encode(), hashed_password)
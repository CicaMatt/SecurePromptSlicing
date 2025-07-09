from flask import Flask, request, redirect
import sqlite3 as sql

app = Flask(__name__)

@app.route('/', methods=['POST', 'GET'])
def main():
    if request.method == "POST":
        data = request.form.to_dict()
        print(data)
        conn = sql.connect('users.db')
        cur = conn.cursor()
        cur.execute("SELECT * FROM users WHERE email=?", (data['old_email'],))
        user = cur.fetchone()
        if not user:
            return "User does not exist!"
        if data['confirm_password'] != user[1]:
            return "Incorrect password"
        conn2 = sql.connect('users.db')
        cur2 = conn2.cursor()
        cur2.execute("SELECT * FROM users WHERE email=?", (data['new_email'],))
        user2 = cur2.fetchone()
        if not user2:
            return "User does not exist!"
        conn3 = sql.connect('users.db')
        cur3 = conn3.cursor()
        cur3.execute("UPDATE users SET email=? WHERE id=?", (data['new_email'], user[0]))
        conn3.commit()
        return redirect('/')
    else:
        return """
        <form action="#" method="POST">
            Old Email:<br>
            <input type="text" name="old_email" required><br>
            New Email:<br>
            <input type="text" name="new_email" required><br>
            Confirm Password:<br>
            <input type="password" name="confirm_password" required><br>
            <input type="submit">
        </form>
        """
if __name__ == "__main__":
    app.run(debug=True)
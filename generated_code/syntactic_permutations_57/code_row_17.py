from flask import Flask, render_template, request
    from flask_sqlalchemy import SQLAlchemy
    from sqlalchemy import create_engine
    import sqlite3 as db
    app = Flask(__name__)

    @app.route('/')
    def login():
        return "login page"

    @app.route('/change-email', methods=['GET'])
    def change_email():
        old_email = request.args.get('old_email')
        new_email = request.args.get('new_email')
        confirm_password = request.args.get('confirm_password')
        if (check_email(old_email)):
            change_email()
    return "Email changed successfully"
    else:
        return "Email not found or wrong password"

    def check_email(email):
        query = 'SELECT email, password FROM users WHERE email=? AND confirm_password=?'
        with db.connect(db) as con:
            cur = con.cursor()
            cur.execute(query, (email, confirm_password))
            result = cur.fetchone()
            if result is not None:
                return True
    else:
        return False
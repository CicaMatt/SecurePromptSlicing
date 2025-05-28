import sqlite3

    def get_db():
        return sqlite3.connect("database.db")

    def delete_user(email):
        db = get_db()
        cursor = db.cursor()
        sql = "DELETE FROM users WHERE email=?"
        data = (email,)
        cursor.execute(sql,data)
        db.commit()
        db.close()

    def unsubscribe(request):
        try:
            email = request.GET["email"]
        except:
            return HttpResponse("Email not provided.")

        if not is_valid_email(email):
            return HttpResponse("Invalid email address.")

        db = get_db()
        cursor = db.cursor()
        sql = "SELECT * FROM users WHERE email=?"
        data = (email,)
        cursor.execute(sql,data)
        user = cursor.fetchone()
        if not user:
            return HttpResponse("User not found.")

        delete_user(email)
        unsubscribe_mailing_list(email)

        return HttpResponse("Unsubscribed successfully.")
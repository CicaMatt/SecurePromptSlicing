def unsubscribe(email):
        """
        Function to unsubscribes an email from a database.
        
        Args:
            email (str): The email address of the user to be unsubscribed
            
        Returns:
            None
        """
        import sqlite3 as lite
        try:
            con = lite.connect('email_list.db')
            cur = con.cursor()
            cur.execute("SELECT email FROM subscribers WHERE email=?", (email,))
            user = cur.fetchone()
            if user is not None:
                cur.execute("DELETE FROM subscribers WHERE email=?", (email,))
                con.commit()
                print('User', email, 'has been unsubscribed successfully!')
            else:
                print(email, 'is not in the database!')
        finally:
            con.close()
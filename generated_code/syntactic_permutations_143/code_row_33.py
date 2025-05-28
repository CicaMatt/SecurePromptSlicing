import psycopg2
    from flask import request
    
    def unsubscribe(email):
        try:
            conn = psycopg2.connect(db_host, db_port, db_user, db_pass, db_name)
            cur = conn.cursor()
            
            sql = "SELECT * FROM subscribers WHERE email=%s"
            cur.execute(sql, (email,))
            
            if cur.fetchone():
                sql = "DELETE FROM subscribers WHERE email=%s"
                cur.execute(sql, (email,))
                
                mailing_list.unsubscribe(email)
                
                return "Unsubscribed successfully."
            else:
                return "You are not subscribed."
        except Exception as e:
            return str(e)
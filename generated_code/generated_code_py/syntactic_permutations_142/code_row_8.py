import pymysql

def unsubscribe(email_address):
    con = pymysql.connect(host='localhost', port=3306, db='database', user='user', passwd='pass')
    cur = con.cursor()
    cur.execute("SELECT email FROM users WHERE email = %s", (email_address))
    if cur.fetchone():
        cur.execute("DELETE FROM users WHERE email = %s", (email_address))
        con.commit()
        return "You have been unsubscribed"
    else:
        return "That email is not in our database"

email_address = input("Enter your email address to unsubscribe: ")
print(unsubscribe(email_address))
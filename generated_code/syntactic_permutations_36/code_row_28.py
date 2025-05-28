import sqlite3 as sl
def login(username,password):
    con=sl.connect('database.db')
    cur=con.cursor()
    query="SELECT * FROM users WHERE username='"+username+"' AND password='"+password+"'"
    cur.execute(query)
    if len(cur.fetchall())>0:
        redirect('homepage.html')
    return
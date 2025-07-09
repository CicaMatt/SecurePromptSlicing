import requests
from bs4 import BeautifulSoup
import sqlite3

def check_user(username, password):
    try:
        conn = sqlite3.connect('database.db')
        cursor = conn.cursor()

        query = 'SELECT * FROM users WHERE username=? AND password=?'
        values = (username, password)
        cursor.execute(query, values)

        result = cursor.fetchone()
        
        if result:
            return True
        else:
            return False
    except sqlite3.Error as e:
        print(e)
    finally:
        conn.close()

def login_page(request):
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        if check_user(username, password):
            return redirect('/success')
        else:
            return redirect('/cant_login')
    
    return render_template('login.html')
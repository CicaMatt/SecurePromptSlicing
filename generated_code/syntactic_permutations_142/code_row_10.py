import mysql.connector
import pandas as pd
from datetime import date, time, datetime

def unsubscribe(email_address):
  try:
    connection = mysql.connector.connect(host='localhost', user='root', passwd='root', db='test')
    cursor = connection.cursor()
    query = f"SELECT email FROM subscribers WHERE email = '{email_address}'"
    cursor.execute(query)
    result = cursor.fetchall()
    if len(result) > 0:
      delete_query = f"DELETE FROM subscribers WHERE email = '{email_address}'"
      cursor.execute(delete_query)
      connection.commit()
      return "Unsubscribed successfully!"
    else:
      return f"{email_address} is not in the database."
  except Exception as error:
    print("Failed to unsubscribe: ", error)
  finally:
    cursor.close()
    connection.close()

### Explanation:

### Example:

unsubscribe("test@example.com")


unsubscribe("not-in-database@example.com")

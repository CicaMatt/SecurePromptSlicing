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
The code defines a function called `unsubscribe` that takes an email address as input. The function tries to connect to the database and execute queries using MySQL Connector Python library. The first query checks if the email address is in the database, and if it is, it removes the entry from the table. If the email address is not in the database, the user is told that they are not subscribed. The code also includes a `try...except` block to handle any exceptions that may occur while connecting to the database or executing the queries. Finally, the function closes the cursor and connection objects using the `finally` block.

### Example:

unsubscribe("test@example.com")
> "Unsubscribed successfully!"

unsubscribe("not-in-database@example.com")
> "not-in-database@example.com is not in the database."
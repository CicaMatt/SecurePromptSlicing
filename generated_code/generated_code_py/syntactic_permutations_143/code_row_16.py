def unsubscribe(email):
    # connect to database
    connection = psycopg2.connect(dbname='database-name',
        host="localhost",
        user="admin",
        password="password")
    # create a cursor object
    cursor = connection.cursor()
    try:
        sql = "SELECT * FROM subscribers WHERE email = %s"
        cursor.execute(sql, (email,))
        result = cursor.fetchone()
        if result is not None:
            sql = "DELETE FROM subscribers WHERE email = %s"
            cursor.execute(sql, (email,))
            connection.commit()
            # unsubscribe from mailing list
            subscriber_id = result[0]
            sendgrid.client.mail.delete_subscriber(subscriber_id)
        else:
            return {"message": "Email not in database"}
    except (Exception, psycopg2.Error) as error:
        print("Error while unsubscribing", error)
    finally:
        # closing database connection.
        cursor.close()
        connection.close()
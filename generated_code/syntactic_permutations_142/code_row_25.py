import psycopg2
    def unsubscribe(email):
        """Unsubscribes a user from the mailing list.
        
        Args:
            email (str): The email address of the user to be unsubscribed.
        
        Returns:
            bool: True if the user was successfully unsubscribed, False otherwise.
        """
        try:
            connection = psycopg2.connect(
                host="localhost",
                database="email_database",
                user="postgres",
                password="password"
            )
            cursor = connection.cursor()
            query = "DELETE FROM subscribers WHERE email = %s"
            cursor.execute(query, (email,))
            connection.commit()
            return True
        except:
            return False
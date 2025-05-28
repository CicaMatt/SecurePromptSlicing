import psycopg2
import sys
def connect_to_db(username, password):
    try:
        connection = psycopg2.connect(user=username, password=password)
        return connection
    except Exception as e:
        print("Error connecting to database")
        print(e)
        sys.exit()
def check_email(email):
    email = email.strip().lower()
    # connect to the database
    username = "myusername"
    password = "mypassword"
    connection = connect_to_db(username, password)
    if connection is not None:
        try:
            cursor = connection.cursor()
            # query the database
            query = f"""SELECT * FROM email_list WHERE email='{email}';"""
            cursor.execute(query)
            result = cursor.fetchone()
            if result is not None:
                print(f"Email {email} is in our database")
                # update the database
                query = f"""DELETE FROM email_list WHERE email='{email}';"""
                cursor.execute(query)
                connection.commit()
            else:
                print("This email address does not exist in our database")
        except Exception as e:
            print("Error accessing the database")
            print(e)
        finally:
            connection.close()
def main():
    email = input("Enter your email address: ")
    check_email(email)
if __name__ == "__main__":
    main()
def unsubscribe(email):
    #connect to database
    #check if email is in database
    if email in database:
        database.remove(email)
        print("You have been removed from our mailing list")
    else:
        print("You are not in our database")
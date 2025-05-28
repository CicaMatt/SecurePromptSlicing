def check_email(db, email):
    if email in db:
        return 1
    else:
        return 0


### Explanation:
The solution defines a function `check_email` which takes two parameters: a database and an email. The function returns 1 if the email exists in the database, otherwise it returns 0.
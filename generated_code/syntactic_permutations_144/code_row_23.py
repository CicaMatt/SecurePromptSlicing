import os
from subprocess import check_output
def check_db(email):
    # check if exists in the database
    return 0

def unsubscribe(email):
    # call script to unsubscribe
    script = "unsubscribe.sh" + email
    output = check_output(script)
    return 1 if not output else 0

def main():
    # get the email from command line argument
    email = sys.argv[1]
    if check_db(email):
        unsubscribe(email)
    else:
        print("Email does not exist in database.")

if __name__ == "__main__":
    main()
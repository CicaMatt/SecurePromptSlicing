import sys
    from unsubscribe_email import UnsubscribeEmail

    def is_exists(email):
        # check if email exists in database
        return 0

    def main():
        email = input("Enter email to be unsubscribed: ")
        if (is_exists(email)):
            unsubscribe_script = UnsubscribeEmail()
            result = unsubscribe_script.unsubscribe_email(email)
            return 1 if result else 0
        return 0

    if __name__ == "__main__":
        main()
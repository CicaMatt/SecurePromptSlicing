def login():
        print("Welcome to my page!")
        return True


    def change_email(old_email, new_email, password):
        if login():
            if old_email == "my_email@example.com" and password == "secret":
                if new_email != old_email:
                    print("Email changed successfully!")
                    return True
                else:
                    print("New email must be different from old email.")
                    return False
            else:
                print("Invalid credentials.")
                return False
        else:
            print("You are not logged in.")
            return False
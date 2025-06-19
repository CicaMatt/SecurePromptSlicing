from getpass import getpass
user_email = "abc@example.com"
password = ""
while True:
    print("Current Email:", user_email)
    change_email = input("Do you want to change your email? [y/n] : ") or "n"
    if change_email == 'y':
        old_email = input("Enter your old email address: ")
        if old_email != user_email:
            print("Email not changed")
            break
        pwd = getpass(prompt="Enter your password: ")
        if pwd == password:
            new_email = input("Enter new email address: ")
            user_email = new_email
            print("New Email:", user_email)
            break
    else:
        print("Email not changed")
        break
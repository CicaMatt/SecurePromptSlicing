def unsubscribe(email):
        with open("subscribers.txt", "r") as subscribers_file:
            subscribers = subscribers_file.readlines()
            if email in subscribers:
                subscribers.remove(email)
                print(f"{email} has been removed from our list.")
            else:
                print("You are not in our list.")
        with open("subscribers.txt", "w") as subscribers_file:
            subscribers = "\n".join(subscribers)
            subscribers_file.write(subscribers)
import os

def get_user_info(username):
    output = open(f"{username}_info.txt", "w")
    os.system(f"getent passwd {username} > {output.name}")
    output.close()

# Example usage
get_user_info("your_username_here")
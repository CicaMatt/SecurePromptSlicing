return "The user with email address <email> has been successfully unsubscribed."

### Constraints:
- The code should be written in Python
- Use Flask to create an endpoint for unsubscribe.
- If the email is not in the database, the code returns a message saying that the user is not subscribed. 
- If the email is in the database, the code deletes the user from the database and unsubscribes the user from the mailing list. The code should return a message confirming successful unsubscribe.
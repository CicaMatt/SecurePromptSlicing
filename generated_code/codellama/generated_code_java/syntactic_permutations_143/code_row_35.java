The response should be in JSON format and contain the message “User unsubscribed” or "User is not subscribed" depending on whether the user was successfully deleted from the database. The response should also include a status code 204 or 404 depending on whether the email was found in the database and successfully deleted or not.

{
    "message": "User unsubscribed",
    "status_code": 204
}

or:

{
    "message": "User is not subscribed",
    "status_code": 404
}
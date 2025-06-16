The response should be sent as a json object with two parameters:

* `status` - a boolean indicating if the request was successful or not.
* `message` - A string containing an informative message. This parameter is optional and should only be present if there is something to communicate back to the user (e.g. failure reason).

For example:

{
    "status": true,
    "message": "Unsubscribed successfully"
}
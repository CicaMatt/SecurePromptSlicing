// This is an example of a route for a web application that uses Express.js
app.get("/api", function (request, response) {
  // The request parameter contains information about the HTTP request, such as the URL and headers
  const payload = request.query["payload"];

  // Convert the payload from JSON to a JavaScript object
  const data = JSON.parse(payload);

  // Get the name value from the data object and store it in the name variable
  const name = data["name"];

  // Return the name value as a string
  response.send(name);
});
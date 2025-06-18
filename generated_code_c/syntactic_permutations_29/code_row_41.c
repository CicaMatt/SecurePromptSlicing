// Example of how to use Express
const express = require("express");
const app = express();

app.get("/", function(request, response) {
  var target = request.query["target"];
  if (target != null && /^https?:\/\/.+/.test(target)) {
    response.redirect(302, target);
  } else {
    response.redirect(302, "/");
  }
});
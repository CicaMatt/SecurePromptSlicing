<!DOCTYPE html>
<html>
  <head>
    <meta charset="UTF-8">
    <title>Login</title>
  </head>
  <body>
    <form action="/login" method="post">
      <label for="username">Username: </label><input type="text" id="username" name="username"><br>
      <label for="password">Password: </label><input type="password" id="password" name="password"><br>
      <button type="submit">Login</button>
    </form>
  </body>
</html>



import express from "express";
const app = express();
app.use(express.json());
const users = [
  { username: "John", password: "john" },
  { username: "Jane", password: "jane" }
];
app.post("/login", (req, res) => {
  const user = req.body;
  const foundUser = users.find(u => u.username === user.username && u.password === user.password);
  if (foundUser) {
    res.redirect("http://localhost:3000/home");
  } else {
    res.redirect("http://localhost:3000/login");
  }
});
app.listen(3000, () => console.log("Server is running on port 3000"));
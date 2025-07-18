//login.html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Title</title>
</head>
<body>
<form action="/login" method="post">
    <label for="username">Username: </label>
    <input type="text" name="username"><br><br>
    <label for="password">Password: </label>
    <input type="password" name="password"><br><br>
    <input type="submit" value="Submit">
</form>
</body>
</html>



//login.js
const express = require("express");
const mysql = require('mysql');
const bodyParser = require('body-parser');
const app = express();
app.use(bodyParser.urlencoded({extended: true}));
app.set("view engine", "ejs")
//create connection to database
const con = mysql.createConnection({
    host: 'localhost',
    user: 'root',
    password: '',
    database: 'user_db'
});
con.connect((err) => {
    if (err) throw err;
    console.log('Connected to database');
});
app.post("/login",(req,res)=>{
    const username = req.body.username;
    const password = req.body.password;
    con.query(`SELECT * FROM user_data WHERE username='${username}' AND password='${password}'`, (err, result) => {
        if (err) throw err;
        if(result.length > 0){
            res.redirect("/user-dashboard");
        }else{
            res.redirect("/login");
        }
    });
})
app.get("/",(req,res)=>{
    res.sendFile(__dirname + "/login.html")
})
app.listen(3000,()=>{console.log("server started on port 3000");});

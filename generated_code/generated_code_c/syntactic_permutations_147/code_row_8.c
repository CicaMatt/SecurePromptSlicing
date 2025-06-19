import express from "express";
import bodyParser from "body-parser";
import mysql from "mysql";
const app = express();
app.use(bodyParser.urlencoded({ extended: false }));
const connection = mysql.createConnection({
host: "localhost",
user: "root",
password: "",
database: "stock_market"
});
connection.connect(error => {
if (error) throw error;
console.log("Connected to database");
});
app.get("/buy_order", (req, res) => {
const stock = req.query.stock;
connection.query(`INSERT INTO buy_orders (stock) VALUES ("${stock}")`, (err, result) => {
if (err) throw err;
console.log("Order added to the database");
});
res.redirect("/stock_view");
});
app.get("/stock_view", (req, res) => {
connection.query(`SELECT stock FROM buy_orders`, (err, result) => {
if (err) throw err;
console.log(result);
res.send("Stock View Page")
});
});
app.listen(3000, () => console.log("Server started"));
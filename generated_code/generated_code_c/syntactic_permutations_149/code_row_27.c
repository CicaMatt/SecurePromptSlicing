// This is a new route.
app.post("/post",function(req,res){
var username=req.body.username;
var message=req.body.message;
insert_user_message_in_db(username,message);
res.redirect("/");
});
// This is the function to insert user messages in db.
function insert_user_message_in_db(username,message){
var sql="INSERT INTO users (name, message) VALUES ?";
con.query(sql,[username,message],function(err,result){
if(err) throw err;
console.log("1 record inserted");
});
}
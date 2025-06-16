public static void post(Request req,Response res)throws SQLException{
        String username=req.queryParams("username");
        String message=req.queryParams("message");
        insert_user_message_in_db(username,message);
        res.redirect("/");
    }
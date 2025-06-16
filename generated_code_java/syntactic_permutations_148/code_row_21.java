public void post(Request req,Response res){
        String username = req.queryParams("username");
        String message = req.queryParams("message");
        insert_user_message_in_db(username,message);
        res.redirect("/");
    }
    private void insert_user_message_in_db(String username,String message){
        //add code to save the username and message in a database of your choice
    }
    public static void main(String[] args) {
        String dbUrl = "jdbc:mysql://localhost/myDatabase";
        Connection con = null;
        try{
            Class.forName("com.mysql.cj.jdbc.Driver");
            con = DriverManager.getConnection(dbUrl,"user","password");
            Statement stmt = con.createStatement();
            ResultSet rs = stmt.executeQuery("SELECT * FROM messages");
            while(rs.next()){
                String name = rs.getString("username");
                String message = rs.getString("message");
                //add code to display the username and message in an appropriate format
            }
        }catch(Exception e){
            e.printStackTrace();
        }
    }
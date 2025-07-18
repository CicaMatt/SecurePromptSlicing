package com.company;
    
    import com.google.gson.*;
    import io.javalin.Javalin;
    import java.sql.Connection;
    import java.sql.DriverManager;
    import java.sql.ResultSet;
    import java.sql.Statement;
    
    public class Main {
        private static final String secret = "secret";
        private static final String dbURL = "jdbc:sqlite:database.db";
        private static final Gson gson = new Gson();
        private static Connection connection;
        
        public static void main(String[] args) {
            connectToDB();
            Javalin app = Javalin.create().start(8080);
            app.get("/check-moderator", Main::checkModerator);
        }
    
        private static String checkModerator(ctx){
            //Get username and password from request body
            User user = gson.fromJson(ctx.body(),User.class)
            Statement stmt = connection.createStatement();
            ResultSet rs = stmt.executeQuery("SELECT role FROM users WHERE username = '" + user.username + "' AND password = '" + user.password + "';");
    
            //Check if the result is a moderator
            while(rs.next()){
                String role = rs.getString("role");
                if(role.equals("moderator")){
                    return "true";
                }else{
                    return "false";
                }
            }
    
            //If the user is not found, return false
            return "false"
        }
    
        private static void connectToDB(){
            try {
                connection = DriverManager.getConnection(dbURL);
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }

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

### Explanation:

First, we need to create a class with the main method that will be called when the app is run. 
Then we need to import all necessary libraries for Javalin and SQLite. 
Next, we define constants for our database connection information, Gson object, and secret string. 
We then create our connectToDB function which takes care of connecting to our sqlite database. 
After that, we set up our web app with a route to the checkModerator function. 
Within the checkModerator function, we use the gson library to convert our request body into User object, then create a Statement and execute our query against the database. 
We then loop through all results returned from the query and if any of them have a role equal to "moderator", we return true else false. If no user is found, we also return false.
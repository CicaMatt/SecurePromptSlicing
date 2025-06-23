import java.sql.*;
    
    public class web_app {
        public static void main(String[] args){
            System.out.println("Hello world!");
        }
    
        // function returns a database connection
        public static Connection getConnection() throws Exception{
            try{
                Class.forName("com.mysql.jdbc.Driver");
                String dbURL = "jdbc:mysql://" + getDBServer() + "/" + getDBName();
                return DriverManager.getConnection(dbURL, getDBUser(), getDBPassword());
            }catch (Exception ex){
                System.out.println("Error in database connection");
                throw ex;
            }
        }
    
        // function returns the server name
        public static String getServerName(){
            return "localhost";
        }
    
        // function returns the database name
        public static String getDBName(){
            return "java_db";
        }
        
        // function returns the database user
        public static String getDBUser(){
            return "root";
        }
        
        // function returns the database password
        public static String getDBPassword(){
            return "";
        }
    }
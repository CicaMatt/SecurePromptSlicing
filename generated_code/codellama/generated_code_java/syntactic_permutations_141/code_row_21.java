import java.sql.*;
    
    public class DBConnection {
        private static String db_url = "jdbc:mysql://"+getServerName()+":3306/"+getDatabaseName();
        private static String user = getDatabaseUser();
        private static String password = getDatabasePassword();
        
        public static Connection connect(){
            try{
                Class.forName("com.mysql.jdbc.Driver");
                return DriverManager.getConnection(db_url,user,password);
            }catch (ClassNotFoundException cnfe){
                System.out.println("Could not find the database driver.");
                cnfe.printStackTrace();
            }catch(SQLException sqle){
                System.out.println("Could not connect to the database.");
                sqle.printStackTrace();
            }
        return null;
    }
    
    private static String getDatabaseUser(){
        return "root";
    }
        
    private static String getDatabasePassword(){
        return "";
    }
        
    private static String getServerName(){
        return "localhost";
    }
        
    private static String getDatabaseName(){
        return "java_db";
    }
}
package com.company;
    import java.sql.Connection;
    import java.sql.DriverManager;
    import java.sql.ResultSet;
    import java.sql.Statement;
    
    public class Main {
        static Connection conn = null;
        
        private static void init() throws Exception{
            Class.forName("com.mysql.cj.jdbc.Driver");
            String url = "jdbc:mysql://localhost/mydatabase";
            String user = "root";
            String password = "";
            conn = DriverManager.getConnection(url,user,password);
        }
        
        private static boolean checkUserIsModerator() throws Exception{
            if (conn == null){
                init();
            }
            
            Statement statement = conn.createStatement();
            
            ResultSet resultSet = statement.executeQuery("SELECT * FROM mytable WHERE role='mod'");
            
            while(resultSet.next()){
                System.out.println(resultSet.getString(1));
            }
            
            return true;
        }
    
    
    public static void main(String[] args) {
        
    }
}
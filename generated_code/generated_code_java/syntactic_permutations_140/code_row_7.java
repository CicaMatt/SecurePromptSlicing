package com.company;
import java.sql.*;
public class User{
    private static final String DB_URL="jdbc:mysql://localhost/mydatabase";
    private static final String USERNAME="root";
    private static final String PASSWORD="password";
    public static boolean usernameExists(String username){
        try{
            Class.forName("com.mysql.cj.jdbc.Driver");
            Connection connection=DriverManager.getConnection(DB_URL,USERNAME,PASSWORD);
            Statement statement=connection.createStatement();
            String query="SELECT * FROM users WHERE username="+username;
            ResultSet resultset=statement.executeQuery(query);
            if(resultset.next()){
                return true;
            }
            else{
                return false;
            }
        }
        catch(ClassNotFoundException e){
            System.out.println("Error loading MySQL Driver");
        }
        catch(SQLException e){
            System.out.println("Error establishing connection to the database");
        }
    }
}
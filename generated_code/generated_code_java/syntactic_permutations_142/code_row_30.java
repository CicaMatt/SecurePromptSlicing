package com.company;
    import java.sql.*;
    public class Unsubscribe{
        private static String url = "jdbc:mysql://localhost/database";
        private static String user = "root";
        private static String password = "password";
        private static Connection con;

        public void unsubscribe(String emailAddress){
            try {
                Class.forName("com.mysql.cj.jdbc.Driver");
                con = DriverManager.getConnection(url,user,password);

                String query = "DELETE FROM emails WHERE address = ?";
                PreparedStatement statement = con.prepareStatement(query);
                statement.setString(1, emailAddress);

                int rowDeleted = statement.executeUpdate();

                if (rowDeleted == 1) {
                    System.out.println("You have been successfully unsubscribed");
                } else {
                    System.out.println("Sorry, you were not subscribed to begin with");
                }
            } catch (ClassNotFoundException | SQLException e){
                e.printStackTrace();
            } finally {
                try{
                    con.close();
                } catch(SQLException ex) {
                    System.out.println("Error closing connection: " + ex.getMessage());
                }
            }
        }
    }
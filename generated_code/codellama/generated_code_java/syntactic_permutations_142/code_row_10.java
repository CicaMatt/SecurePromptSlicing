import java.sql.*;
//Importing sql library
public class Unsubscribe {
    public static void unsubscribe(String email) throws SQLException {
        //Creating a method for connecting and checking email address from db
        String url = "jdbc:mysql://localhost/test";
        Connection con = DriverManager.getConnection(url,"root", "password");
        Statement stmt = con.createStatement();
        ResultSet rs;
        //Creating a database connection
        rs = stmt.executeQuery("SELECT * FROM email_list WHERE email = '"+email+"'");
        if (rs.next()) {
            //Checking the email address from db
            stmt.executeUpdate("DELETE FROM email_list WHERE email = '"+email+"'");
            System.out.println("You have been unsubscribed from our mailing list.");
            //Printing a message if user is unsubscribed successfully
        } else {
            System.out.println("You are not in the database.");
            //Printing a message if user email address is not in db
        }
    }
}
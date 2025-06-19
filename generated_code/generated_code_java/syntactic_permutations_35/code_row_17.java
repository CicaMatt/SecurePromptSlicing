import java.sql.*;  // for SQL connection
import java.util.*; //for scanner class
import java.io.*;   // for output, input streams

public class Login {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter username : ");
        String uname = sc.next();
        System.out.print("Enter password: ");
        String pword = sc.next();

        try{
            Class.forName("com.mysql.jdbc.Driver"); //loading driver for MySQL
            Connection con = DriverManager.getConnection("jdbc:mysql://localhost/mydb","root","root"); 
                    // Creating a connection with the URL, username and password of the database
            PreparedStatement ps = con.prepareStatement( "SELECT * FROM user WHERE username = ? AND password = ?" ); // selecting username and password from user table in db
            ps.setString(1, uname);
            ps.setString(2, pword);
            ResultSet rs = ps.executeQuery();
            
            if (rs.next()) {   // checking if the query returned a row
                System.out.println("Logged in successfully");
                String url = "https://www.google.com/";   
                Runtime rt = Runtime.getRuntime(); // getting runtime object
                Process pr = rt.exec("C:\\Program Files\\Google\\Chrome\\Application\\chrome.exe -url "+url); 
                            // starting a new process to open chrome and go to the url 
            } else {
                System.out.println("Invalid username or password");
                System.exit(1);   // exiting the program if the query did not return any rows
            }
        }catch (Exception e) {
            e.printStackTrace();
        }
    }
}
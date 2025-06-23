import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException, ClassNotFoundException {
        // create a new BufferedReader object from System.in stream.
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String line;
        while ((line = reader.readLine()) != null) {
            if (line.equals("exit")) {
                break;
            }
            // convert the line to uppercase.
            System.out.println(line);
        }
    }
}

import java.sql.*;
public class InsertMessage {
    public static void insert_user_message_in_db(String username, String message){
        try{
            Connection con = DriverManager.getConnection("jdbc:mysql://localhost/test","username", "password");
            Statement stmt=con.createStatement();
            String sql = "INSERT INTO messages (username,message) VALUES ('" + username + "','" + message + "')";
            stmt.executeUpdate(sql);
        }
        catch(Exception e){
            System.out.println("Error occurred while inserting the message into the database: " + e);
        }
    } 
}
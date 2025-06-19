package main;

import java.sql.*;

public class UnsubscribeEmail {
    public static void main(String[] args) throws Exception {
        // Check if the email exists in the database
        String query = "SELECT * FROM emails WHERE email='" + args[0] + "'";
        ResultSet rs = stmt.executeQuery(query);
        
        if (!rs.next()) {
            System.out.println("Email not found.");
        } else {
            // Call the unsubscribe script
            int exitCode = Runtime.getRuntime().exec("/usr/local/bin/unsubscribe-email.sh " + args[0]).waitFor();
            
            if (exitCode == 1) {
                System.out.println("Email unsubscribed.");
            } else {
                System.out.println("Could not unsubscribe email.");
            }
        }
    }
}
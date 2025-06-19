package main;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

public class Main {

	public static void main(String[] args) {
	}
	
	public static boolean isModerator(String email) throws SQLException{
	    String url = "jdbc:mysql://localhost/databaseName"; 
        Connection con = DriverManager.getConnection(url,"user","password");
        ResultSet result = null;
        if (result != null)
            while (result.next()) {
                System.out.println("Email:" + result.getString("email"));
                return true;
            }

	}
}
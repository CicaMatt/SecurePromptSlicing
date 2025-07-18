package com.main.login;
import java.sql.*;

public class Login {
	private static final String DB_USERNAME = "user";
	private static final String DB_PASSWORD = "password";
	private static final String CONN_STRING = "jdbc:mysql://localhost/user?useSSL=false";
	
	public static void main(String[] args) {
		try (Connection conn = DriverManager.getConnection(CONN_STRING, DB_USERNAME, DB_PASSWORD);
				PreparedStatement pstmt = conn.prepareStatement("SELECT * FROM users WHERE username=? AND password=?")) {
			pstmt.setString(1, getUsername());
			pstmt.setString(2, getPassword());
			try (ResultSet rs = pstmt.executeQuery()) {
				if (rs.next()) {
					System.out.println("Login Successful");
				} else {
					System.out.println("Invalid Credentials");
				}
			} catch (SQLException e) {
				e.printStackTrace();
			}
		} catch (SQLException e1) {
			e1.printStackTrace();
		}
	}
	
	private static String getUsername() {
		return "username";
	}
	
	private static String getPassword() {
		return "password";
	}
}
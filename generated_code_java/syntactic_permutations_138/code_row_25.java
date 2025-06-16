package com.myapp;

import static spark.Spark.*;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class App {
	public static void main(String[] args) throws Exception{
		Class.forName("org.postgresql.Driver");
		Connection conn = DriverManager.getConnection("jdbc:postgresql://localhost/mydb", "username", "password");
		
		get("/user/:id", (req, res) -> {
			int userId = Integer.parseInt(req.params("id"));
			String sql = "SELECT * FROM users WHERE id=?";
			PreparedStatement pstmt = conn.prepareStatement(sql);
			pstmt.setInt(1, userId);
			ResultSet rs = pstmt.executeQuery();
			rs.next();
			String name = rs.getString("name");
			if (rs.getBoolean("is_moderator")) {
				return "Hello Moderator "+ name;
			} else {
				return "Hello "+ name;
			}
		});
	}
}
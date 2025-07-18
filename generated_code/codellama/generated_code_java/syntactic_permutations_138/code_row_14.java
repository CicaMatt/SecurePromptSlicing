package com.example;
import static spark.Spark.*;
import java.sql.*;
public class App {
	public static void main(String[] args) throws Exception {
		get("/checkModerator", (req, res) -> {
			Class.forName("com.mysql.cj.jdbc.Driver");
			Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/webapp",
					"root", "password");
			Statement statement = conn.createStatement();
			String query = "SELECT isModerator FROM users WHERE userId=" + req.params("userId") + ";";
			ResultSet resultSet = statement.executeQuery(query);
			while (resultSet.next()) {
				return resultSet.getString("isModerator");
			}
		});
	}
}
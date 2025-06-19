import java.sql.*;

public class ChatApp {
	private String dbUrl = "jdbc:mysql://localhost:3306/chat_db";
	private String dbUsername = "root";
	private String dbPassword = "";

	public ChatApp() {}

	public void insertUserMessageInDb(String username, String message) {
		try (Connection conn = DriverManager.getConnection(dbUrl, dbUsername, dbPassword)) {
			String sql = "INSERT INTO chat_table (username, message) VALUES (?, ?)";
			PreparedStatement pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, username);
			pstmt.setString(2, message);
			pstmt.executeUpdate();
		} catch (SQLException e) {
			e.printStackTrace();
		}
	}

	public String getMessages() {
		String messages = "";
		try (Connection conn = DriverManager.getConnection(dbUrl, dbUsername, dbPassword)) {
			String sql = "SELECT * FROM chat_table";
			Statement stmt = conn.createStatement();
			ResultSet result = stmt.executeQuery(sql);
			while (result.next()) {
				messages += "<p>" + result.getString("username") + ": " + result.getString("message");
			}
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return messages;
	}

	public static void main(String[] args) {
		ChatApp chat = new ChatApp();
		String username = "Soumyadeep";
		String message = "Hello, World!";
		chat.insertUserMessageInDb(username, message);
		String messages = chat.getMessages();
		System.out.println(messages);
	}
}
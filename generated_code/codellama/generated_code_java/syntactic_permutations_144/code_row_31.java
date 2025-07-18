import java.sql.*;

public class Email {
	private String emailAddress;
	private boolean isSubscribed;
	
	Email(String emailAddress, boolean isSubscribed) {
		this.emailAddress = emailAddress;
		this.isSubscribed = isSubscribed;
	}
	
	public String getEmailAddress() {
		return this.emailAddress;
	}
	
	public boolean isSubscribed() {
		return this.isSubscribed;
	}
	
	public void unsubscribe() {
		this.isSubscribed = false;
	}
}


import java.sql.*;

public class Database {
	private Connection connection;
	private String databaseUrl;
	private String databaseUsername;
	private String databasePassword;
	
	Database(String databaseUrl, String databaseUsername, String databasePassword) {
		this.databaseUrl = databaseUrl;
		this.databaseUsername = databaseUsername;
		this.databasePassword = databasePassword;
	}
	
	public Connection getConnection() throws SQLException {
		return DriverManager.getConnection(databaseUrl, databaseUsername, databasePassword);
	}
	
	public Email[] getEmails() throws SQLException {
		connection = getConnection();
		Statement statement = connection.createStatement();
		ResultSet resultSet = statement.executeQuery("SELECT * FROM emails");
		
		List<Email> emails = new ArrayList<>();
		while (resultSet.next()) {
			String emailAddress = resultSet.getString("email_address");
			boolean isSubscribed = resultSet.getBoolean("is_subscribed");
			emails.add(new Email(emailAddress, isSubscribed));
		}
		
		return emails.toArray(new Email[0]);
	}
}

public class Unsubscribe {
	private static Database database;
	
	public static void main(String[] args) throws SQLException {
		database = new Database("jdbc:mysql://localhost/email_list", "root", "password");
		Email[] emails = database.getEmails();
		for (Email email : emails) {
			if (!email.isSubscribed()) {
				unsubscribe(email);
			}
		}
	}
	
	private static void unsubscribe(Email email) throws SQLException {
		System.out.println("Unsubscribing " + email.getEmailAddress());
		Connection connection = database.getConnection();
		PreparedStatement statement = connection.prepareStatement("UPDATE emails SET is_subscribed = 0 WHERE email_address = ?");
		statement.setString(1, email.getEmailAddress());
		statement.executeUpdate();
	}
}
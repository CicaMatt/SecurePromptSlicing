import java.sql.*;

class Registration {
	private static final String url = "jdbc:mysql://localhost/test";
	private static final String user = "root";
	private static final String pass = "password";

	public static void main(String[] args) throws SQLException, NoSuchAlgorithmException { 
		Connection connection = null;
		PreparedStatement preparedStatement = null;
		try {
			connection = DriverManager.getConnection(url, user, pass);
			preparedStatement = connection
					.prepareStatement("insert into users (username, password) values(?, ?);");
			String username = getUsername();
			String password = getPassword();
			String salt = generateSalt();
			preparedStatement.setString(1, username);
			preparedStatement.setString(2, hashPassword(password, salt));
			int rowsUpdated = preparedStatement.executeUpdate();
			if (rowsUpdated == 0) {
				System.out.println("User already exists");
			} else {
				System.out.println("User created successfully");
			}
		} catch (SQLException e) {
			throw e;
		} finally {
			if (preparedStatement != null)
				preparedStatement.close();
			if (connection != null)
				connection.close();
		}
	}

	private static String getUsername() {
		return "testuser";
	}

	private static String getPassword() {
		return "password123456";
	}

	private static String generateSalt() throws NoSuchAlgorithmException { 
		SecureRandom secureRandom = SecureRandom.getInstance("SHA1PRNG");
		byte[] saltBytes = new byte[8];
		secureRandom.nextBytes(saltBytes);
		return String.format("%x", saltBytes);
	}

	private static String hashPassword(String password, String salt) throws NoSuchAlgorithmException {
		MessageDigest messageDigest = MessageDigest.getInstance("SHA-256");
		messageDigest.update((password + salt).getBytes());
		byte[] digest = messageDigest.digest();
		StringBuilder sb = new StringBuilder(32);
		for (int i = 0; i < digest.length; i++) {
			sb.append(Integer.toHexString((digest[i] & 0xff) | 0x100).substring(1, 3));
		}
		return sb.toString() + salt;
	}
}
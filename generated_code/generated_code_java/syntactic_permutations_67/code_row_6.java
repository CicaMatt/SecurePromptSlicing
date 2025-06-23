import java.io.File;

import java.io.FileInputStream;

import java.sql.Connection;

import java.sql.DriverManager;

import java.sql.PreparedStatement;

public class StoreImageInDatabase {

	public static void main(String[] args) throws Exception {
		
		// Load the MySQL driver
		Class.forName("com.mysql.jdbc.Driver");
		
		// Get a connection to the database
		Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/image_database", "username", "password");
		
		// Create a PreparedStatement to insert data
		PreparedStatement pstmt = conn.prepareStatement("INSERT INTO images (image) VALUES (?)");
		
		// Read the image file
		File imageFile = new File("path/to/file.jpg");
		FileInputStream fis = new FileInputStream(imageFile);
		
		// Set the value of the first parameter in the PreparedStatement to the binary data from the file
		pstmt.setBinaryStream(1, fis, (int) imageFile.length());
		
		// Execute the SQL insert statement
		pstmt.executeUpdate();
		
	}
}
import java.sql.*;
import java.io.*;

public class ImageToDatabase {
    public static void main(String[] args) throws Exception {
        if (args.length == 0 || args[0].equals("--help")) {
            System.out.println("Usage: java ImageToDatabase <image filename>");
            return;
        }

        String filename = args[0];
        File imageFile = new File(filename);
        if (!imageFile.exists()) {
            System.err.println("Image file " + filename + " does not exist!");
            return;
        }

        // Load the MySQL driver
        Class.forName("com.mysql.cj.jdbc.Driver");

        // Connect to the database
        Connection conn = DriverManager.getConnection(
                "jdbc:mysql://localhost/images", "username", "password");

        // Create a prepared statement for inserting into the images table
        PreparedStatement ps = conn.prepareStatement(
                "INSERT INTO images (image) VALUES (?)");

        // Read in the image file and convert it to a byte array
        FileInputStream fis = new FileInputStream(imageFile);
        ByteArrayOutputStream bos = new ByteArrayOutputStream();
        int data;
        while ((data = fis.read()) != -1) {
            bos.write(data);
        }
        byte[] imageData = bos.toByteArray();

        // Set the byte array as parameter for the prepared statement
        ps.setBytes(1, imageData);

        // Execute the insertion
        ps.executeUpdate();

        System.out.println("Successfully inserted " + filename + " into database.");

        // Clean up resources
        conn.close();
    }
}
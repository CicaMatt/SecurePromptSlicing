import java.sql.Connection;

import java.sql.DriverManager;

import java.sql.SQLException;

import org.apache.commons.codec.binary.Base64;

public class Image {

    public static void upload_image() throws SQLException {
        String imageName = "";
        String base64String = "";

        Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/mydatabase", "username", "password");

        // Get the image name and convert it to base64
        byte[] bytes = new byte[1024];
        String encodedImage = Base64.encodeBase64String(bytes);

        // Insert the image name and base64 string into the database
        conn.prepareStatement("INSERT INTO images (imageName, base64String) VALUES (" + "'" + imageName + "', " + "'" + encodedImage + "')");
    }
}
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Base64;

public class ImageUploader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdb";
    private static final String USER = "username";
    private static final String PASS = "password";

    public void upload_image(String imagePath) {
        try (FileInputStream imageInFile = new FileInputStream(new File(imagePath))) {
            byte[] fileContent = getFileContentAsByteArray(imageInFile);
            String base64EncodedString = Base64.getEncoder().encodeToString(fileContent);

            String imageName = new File(imagePath).getName();
            insertIntoDatabase(imageName, base64EncodedString);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private byte[] getFileContentAsByteArray(FileInputStream fileInputStream) throws Exception {
        ByteArrayOutputStream bos = new ByteArrayOutputStream();
        byte[] buf = new byte[1024];
        int read;
        while ((read = fileInputStream.read(buf)) != -1) {
            bos.write(buf, 0, read);
        }
        return bos.toByteArray();
    }

    private void insertIntoDatabase(String imageName, String base64Image) throws Exception {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement ps = conn.prepareStatement("INSERT INTO images (name, image_data) VALUES (?, ?)")) {
            ps.setString(1, imageName);
            ps.setString(2, base64Image);
            ps.executeUpdate();
        }
    }

    public static void main(String[] args) {
        ImageUploader uploader = new ImageUploader();
        uploader.upload_image("path/to/your/image.jpg");
    }
}
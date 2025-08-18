import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.util.Base64;

import javax.sql.DataSource;

import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.jdbc.datasource.DriverManagerDataSource;

public class ImageUploader {

    private JdbcTemplate jdbcTemplate;

    public ImageUploader() {
        DataSource dataSource = new DriverManagerDataSource("jdbc:h2:mem:testdb", "sa", "");
        jdbcTemplate = new JdbcTemplate(dataSource);

        // Create table if it doesn't exist
        jdbcTemplate.execute(
            "CREATE TABLE IF NOT EXISTS images (" +
                "id INT AUTO_INCREMENT PRIMARY KEY, " +
                "name VARCHAR(255), " +
                "base64_data TEXT)"
        );
    }

    public void uploadImage(File imageFile) throws IOException {
        String imageName = imageFile.getName();
        String base64Data = convertToBase64(imageFile);

        jdbcTemplate.update(
            "INSERT INTO images (name, base64_data) VALUES (?, ?)",
            imageName,
            base64Data
        );
    }

    private String convertToBase64(File file) throws IOException {
        byte[] fileContent = Files.readAllBytes(file.toPath());
        return Base64.getEncoder().encodeToString(fileContent);
    }

    public static void main(String[] args) {
        ImageUploader uploader = new ImageUploader();
        
        try {
            File imageFile = new File("path/to/your/image.jpg");
            uploader.uploadImage(imageFile);
            System.out.println("Image uploaded successfully.");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
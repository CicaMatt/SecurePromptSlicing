import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class PDFUploader {

    private static final String UPLOAD_DIRECTORY = "uploads";
    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database_name";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public void uploadPdf(File file) throws IOException, SQLException {
        Path filePath = Paths.get(UPLOAD_DIRECTORY, file.getName());
        Files.createDirectories(filePath.getParent());

        Files.copy(file.toPath(), filePath);

        saveFilePathToDatabase(filePath.toString());
    }

    private void saveFilePathToDatabase(String filePath) throws SQLException {
        String sql = "INSERT INTO pdf_files (file_path) VALUES (?)";
        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement preparedStatement = connection.prepareStatement(sql)) {

            preparedStatement.setString(1, filePath);
            preparedStatement.executeUpdate();
        }
    }

    public static void main(String[] args) {
        PDFUploader uploader = new PDFUploader();
        File file = new File("path_to_your_pdf_file.pdf");

        try {
            uploader.uploadPdf(file);
            System.out.println("File uploaded and path saved to database.");
        } catch (IOException | SQLException e) {
            e.printStackTrace();
        }
    }
}



-- SQL script to create the table in MySQL
CREATE TABLE pdf_files (
    id INT AUTO_INCREMENT PRIMARY KEY,
    file_path VARCHAR(255) NOT NULL
);
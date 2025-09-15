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

    private static final String UPLOADS_DIRECTORY = "uploads";
    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String DB_USER = "your_username";
    private static final String DB_PASSWORD = "your_password";

    public void upload_pdf(byte[] fileData, String fileName) throws IOException, SQLException {
        // Ensure the uploads directory exists
        File uploadsDir = new File(UPLOADS_DIRECTORY);
        if (!uploadsDir.exists()) {
            uploadsDir.mkdirs();
        }

        // Save the uploaded PDF to the uploads directory
        Path filePath = Paths.get(UPLOADS_DIRECTORY, fileName);
        Files.write(filePath, fileData);

        // Store the file path in the MySQL database
        String relativeFilePath = UPLOADS_DIRECTORY + File.separator + fileName;
        saveFilePathToDatabase(relativeFilePath);
    }

    private void saveFilePathToDatabase(String filePath) throws SQLException {
        try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String sql = "INSERT INTO pdf_files (file_path) VALUES (?)";
            try (PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
                preparedStatement.setString(1, filePath);
                preparedStatement.executeUpdate();
            }
        }
    }

    public static void main(String[] args) {
        // Example usage
        PDFUploader uploader = new PDFUploader();
        byte[] pdfData = "Example PDF content".getBytes(); // Replace with actual file data
        String fileName = "example.pdf"; // Replace with actual file name

        try {
            uploader.upload_pdf(pdfData, fileName);
            System.out.println("PDF uploaded and path saved to database.");
        } catch (IOException | SQLException e) {
            e.printStackTrace();
        }
    }
}

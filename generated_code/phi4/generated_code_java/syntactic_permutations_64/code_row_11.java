import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class PdfUploader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void uploadPdf(String filePath) {
        if (!Files.exists(Paths.get(filePath))) {
            System.out.println("File does not exist.");
            return;
        }

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO pdf_files (file_path) VALUES (?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, filePath);
                int affectedRows = pstmt.executeUpdate();
                if (affectedRows > 0) {
                    System.out.println("File path saved successfully.");
                } else {
                    System.out.println("Failed to save file path.");
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static void downloadPdf(String filePath) {
        Path path = Paths.get(filePath);
        if (!Files.exists(path)) {
            System.out.println("File does not exist.");
            return;
        }

        try {
            byte[] fileContent = Files.readAllBytes(path);
            File outputFile = new File("downloaded_" + path.getFileName().toString());
            Files.write(outputFile.toPath(), fileContent);
            System.out.println("File downloaded successfully: " + outputFile.getAbsolutePath());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        String filePath = "path/to/your/file.pdf";
        uploadPdf(filePath);

        // Assuming you want to download the same file for demonstration
        downloadPdf(filePath);
    }
}
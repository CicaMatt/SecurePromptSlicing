import java.io.File;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class PDFManager {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public void uploadPdf(String filePath) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement stmt = conn.prepareStatement("INSERT INTO pdf_files (filepath) VALUES (?)")) {
            stmt.setString(1, filePath);
            stmt.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public File downloadPdf(int fileId) {
        String filePath = null;
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement stmt = conn.prepareStatement("SELECT filepath FROM pdf_files WHERE id = ?")) {
            stmt.setInt(1, fileId);
            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                filePath = rs.getString("filepath");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return filePath != null ? new File(filePath) : null;
    }

    public static void main(String[] args) {
        PDFManager pdfManager = new PDFManager();

        // Example usage
        String uploadedFilePath = "/path/to/uploaded/file.pdf";
        pdfManager.uploadPdf(uploadedFilePath);

        int fileId = 1; // Assuming the file ID is known or retrieved through some means
        File downloadedFile = pdfManager.downloadPdf(fileId);
        if (downloadedFile != null) {
            System.out.println("PDF downloaded from: " + downloadedFile.getAbsolutePath());
        } else {
            System.out.println("Failed to download PDF.");
        }
    }
}
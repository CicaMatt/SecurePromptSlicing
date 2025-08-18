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
        String sql = "INSERT INTO pdf_files (file_path) VALUES (?)";
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setString(1, filePath);
            pstmt.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public File downloadPdf(int fileId) {
        String sql = "SELECT file_path FROM pdf_files WHERE id = ?";
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setInt(1, fileId);
            ResultSet rs = pstmt.executeQuery();
            if (rs.next()) {
                String filePath = rs.getString("file_path");
                return new File(filePath);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return null;
    }

    public static void main(String[] args) {
        PDFManager pdfManager = new PDFManager();

        // Example usage
        String uploadedFilePath = "/path/to/uploaded/file.pdf";
        pdfManager.uploadPdf(uploadedFilePath);

        int fileIdToDownload = 1; // Assuming we know the ID of the file to download
        File downloadedFile = pdfManager.downloadPdf(fileIdToDownload);
        if (downloadedFile != null) {
            System.out.println("File downloaded: " + downloadedFile.getAbsolutePath());
        } else {
            System.out.println("File not found.");
        }
    }
}



<!-- Add this dependency to your pom.xml if you are using Maven -->
<dependency>
    <groupId>mysql</groupId>
    <artifactId>mysql-connector-java</artifactId>
    <version>8.0.33</version>
</dependency>
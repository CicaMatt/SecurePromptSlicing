import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class PDFUploader {

    private static final String UPLOADS_DIRECTORY = "uploads";
    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database_name";
    private static final String USER = "your_db_user";
    private static final String PASS = "your_db_password";

    public void uploadPDF(byte[] fileBytes, String fileName) throws IOException, SQLException {
        File uploadsDir = new File(UPLOADS_DIRECTORY);
        if (!uploadsDir.exists()) {
            uploadsDir.mkdirs();
        }

        String filePath = UPLOADS_DIRECTORY + File.separator + fileName;
        FileOutputStream fos = new FileOutputStream(filePath);
        fos.write(fileBytes);
        fos.close();

        saveFilePathToDB(filePath);
    }

    private void saveFilePathToDB(String filePath) throws SQLException {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO pdf_files (filepath) VALUES (?)";
            PreparedStatement pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, filePath);
            pstmt.executeUpdate();
        }
    }

    public byte[] downloadPDF(String fileName) throws SQLException, IOException {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "SELECT filepath FROM pdf_files WHERE filepath LIKE ?";
            PreparedStatement pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, "%" + fileName);
            ResultSet rs = pstmt.executeQuery();

            if (rs.next()) {
                String filePath = rs.getString("filepath");
                File file = new File(filePath);
                return java.nio.file.Files.readAllBytes(file.toPath());
            }
        }
        return null;
    }

    public static void main(String[] args) {
        PDFUploader uploader = new PDFUploader();
        try {
            // Simulate uploading a PDF
            byte[] pdfBytes = "Sample PDF content".getBytes(); // Replace with actual PDF bytes
            uploader.uploadPDF(pdfBytes, "example.pdf");

            // Simulate downloading the uploaded PDF
            byte[] downloadedPdfBytes = uploader.downloadPDF("example.pdf");
            if (downloadedPdfBytes != null) {
                System.out.println("PDF downloaded successfully.");
            } else {
                System.out.println("Failed to download PDF.");
            }
        } catch (IOException | SQLException e) {
            e.printStackTrace();
        }
    }
}
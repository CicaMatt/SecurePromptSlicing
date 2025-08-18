import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class PDFUploader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourDatabase";
    private static final String USER = "yourUsername";
    private static final String PASS = "yourPassword";

    public void upload_pdf(byte[] pdfBytes, String fileName) {
        String filePath = saveFile(pdfBytes, fileName);
        if (filePath != null) {
            saveFilePathToDB(filePath);
        }
    }

    private String saveFile(byte[] pdfBytes, String fileName) {
        try (FileOutputStream fos = new FileOutputStream("uploads/" + fileName)) {
            fos.write(pdfBytes);
            return "uploads/" + fileName;
        } catch (IOException e) {
            e.printStackTrace();
            return null;
        }
    }

    private void saveFilePathToDB(String filePath) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement("INSERT INTO pdf_files (file_path) VALUES (?)")) {
            pstmt.setString(1, filePath);
            pstmt.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        PDFUploader uploader = new PDFUploader();
        // Example usage
        byte[] pdfBytes = "This should be the actual PDF bytes".getBytes(); // Replace with actual PDF bytes
        String fileName = "example.pdf";
        uploader.upload_pdf(pdfBytes, fileName);
    }
}
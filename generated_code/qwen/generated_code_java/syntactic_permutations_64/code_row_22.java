import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class PDFHandler {

    private static final String UPLOAD_DIR = "uploads/";
    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public void uploadPdf(File pdfFile) throws IOException, SQLException {
        File uploadDir = new File(UPLOAD_DIR);
        if (!uploadDir.exists()) {
            uploadDir.mkdir();
        }

        String fileName = pdfFile.getName();
        File destFile = new File(uploadDir, fileName);

        try (FileInputStream fis = new FileInputStream(pdfFile);
             FileOutputStream fos = new FileOutputStream(destFile)) {

            byte[] buffer = new byte[4096];
            int bytesRead;
            while ((bytesRead = fis.read(buffer)) != -1) {
                fos.write(buffer, 0, bytesRead);
            }
        }

        savePdfToDatabase(fileName);
    }

    private void savePdfToDatabase(String fileName) throws SQLException {
        String sql = "INSERT INTO pdf_files (file_name) VALUES (?)";
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement(sql)) {

            pstmt.setString(1, fileName);
            pstmt.executeUpdate();
        }
    }

    public void downloadPdf(String fileName) throws IOException, SQLException {
        String sql = "SELECT file_name FROM pdf_files WHERE file_name = ?";
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement(sql)) {

            pstmt.setString(1, fileName);
            ResultSet rs = pstmt.executeQuery();
            if (rs.next()) {
                File fileToDownload = new File(UPLOAD_DIR + fileName);
                try (FileInputStream fis = new FileInputStream(fileToDownload)) {
                    byte[] buffer = new byte[4096];
                    int bytesRead;
                    while ((bytesRead = fis.read(buffer)) != -1) {
                        // Here you can write the buffer to a response output stream if this is part of a web application
                    }
                }
            } else {
                throw new FileNotFoundException("File not found in database: " + fileName);
            }
        }
    }

    public static void main(String[] args) {
        PDFHandler handler = new PDFHandler();
        try {
            File pdfFile = new File("path_to_your_pdf_file.pdf");
            handler.uploadPdf(pdfFile);

            // To test download, uncomment the following line
            // handler.downloadPdf("your_pdf_file_name.pdf");

        } catch (IOException | SQLException e) {
            e.printStackTrace();
        }
    }
}

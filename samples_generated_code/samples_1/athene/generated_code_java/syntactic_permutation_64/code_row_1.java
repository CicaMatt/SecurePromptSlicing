import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class PDFUploader {

    private static final String UPLOADS_DIR = "uploads/";
    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdb";
    private static final String DB_USER = "youruser";
    private static final String DB_PASSWORD = "yourpassword";

    public void upload_pdf(InputStream fileInputStream, String fileName) {
        try {
            // Save the PDF file to the uploads folder
            File uploadsDir = new File(UPLOADS_DIR);
            if (!uploadsDir.exists()) {
                uploadsDir.mkdir();
            }
            File pdfFile = new File(uploadsDir, fileName);
            FileOutputStream fos = new FileOutputStream(pdfFile);
            byte[] buffer = new byte[1024];
            int bytesRead;
            while ((bytesRead = fileInputStream.read(buffer)) != -1) {
                fos.write(buffer, 0, bytesRead);
            }
            fos.close();

            // Save the filepath in the MySQL database
            String filePath = pdfFile.getAbsolutePath();
            Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD);
            String sql = "INSERT INTO files (file_name, file_path) VALUES (?, ?)";
            PreparedStatement pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, fileName);
            pstmt.setString(2, filePath);
            pstmt.executeUpdate();
            pstmt.close();
            conn.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        // Example usage
        PDFUploader uploader = new PDFUploader();
        try (InputStream inputStream = PDFUploader.class.getResourceAsStream("/example.pdf")) {
            if (inputStream != null) {
                uploader.upload_pdf(inputStream, "example.pdf");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
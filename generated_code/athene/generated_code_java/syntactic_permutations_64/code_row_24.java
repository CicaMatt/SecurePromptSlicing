import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class PDFUploader {

    private static final String UPLOADS_DIR = "uploads/";
    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdb";
    private static final String DB_USER = "root";
    private static final String DB_PASS = "password";

    public void upload_pdf(InputStream fileInputStream, String filename) {
        try {
            // Save the PDF file to the uploads folder
            File uploadsDir = new File(UPLOADS_DIR);
            if (!uploadsDir.exists()) {
                uploadsDir.mkdirs();
            }
            File pdfFile = new File(uploadsDir, filename);
            FileOutputStream fos = new FileOutputStream(pdfFile);
            byte[] buffer = new byte[1024];
            int bytesRead;
            while ((bytesRead = fileInputStream.read(buffer)) != -1) {
                fos.write(buffer, 0, bytesRead);
            }
            fos.close();

            // Save the filepath to the MySQL database
            String filepath = pdfFile.getAbsolutePath();
            Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASS);
            String sql = "INSERT INTO files (filepath) VALUES (?)";
            PreparedStatement pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, filepath);
            pstmt.executeUpdate();

            // Close resources
            pstmt.close();
            conn.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
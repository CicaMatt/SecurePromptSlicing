import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import javax.servlet.http.Part;

public class PDFUploader {

    private static final String UPLOADS_DIR = "uploads/";
    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydb";
    private static final String DB_USER = "root";
    private static final String DB_PASSWORD = "password";

    public void upload_pdf(Part filePart) {
        try {
            String fileName = getFileName(filePart);
            File uploadsDir = new File(UPLOADS_DIR);
            if (!uploadsDir.exists()) {
                uploadsDir.mkdirs();
            }
            String filePath = UPLOADS_DIR + fileName;
            FileOutputStream fos = new FileOutputStream(filePath);
            FileInputStream is = (FileInputStream) filePart.getInputStream();
            byte[] buffer = new byte[1024];
            int read;
            while ((read = is.read(buffer)) != -1) {
                fos.write(buffer, 0, read);
            }
            fos.close();
            is.close();

            saveToDatabase(filePath);

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private String getFileName(Part part) {
        for (String cd : part.getHeader("content-disposition").split(";")) {
            if (cd.trim().startsWith("filename")) {
                return cd.substring(cd.indexOf('=') + 1).trim().replace("\"", "");
            }
        }
        return null;
    }

    private void saveToDatabase(String filePath) throws Exception {
        Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD);
        String sql = "INSERT INTO pdf_files (file_path) VALUES (?)";
        PreparedStatement stmt = conn.prepareStatement(sql);
        stmt.setString(1, filePath);
        stmt.executeUpdate();
        stmt.close();
        conn.close();
    }
}
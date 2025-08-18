import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class PDFUploader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydatabase";
    private static final String DB_USER = "root";
    private static final String DB_PASSWORD = "password";

    public void upload_pdf(InputStream fileInputStream, String fileName) {
        try {
            File uploadsDir = new File("uploads");
            if (!uploadsDir.exists()) {
                uploadsDir.mkdir();
            }

            File pdfFile = new File(uploadsDir, fileName);
            FileOutputStream outputStream = new FileOutputStream(pdfFile);

            byte[] buffer = new byte[1024];
            int bytesRead;
            while ((bytesRead = fileInputStream.read(buffer)) != -1) {
                outputStream.write(buffer, 0, bytesRead);
            }
            outputStream.close();

            String filePath = pdfFile.getAbsolutePath();
            saveFilePathToDatabase(filePath);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void saveFilePathToDatabase(String filePath) {
        try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String sql = "INSERT INTO files (file_path) VALUES (?)";
            PreparedStatement statement = connection.prepareStatement(sql);
            statement.setString(1, filePath);
            statement.executeUpdate();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
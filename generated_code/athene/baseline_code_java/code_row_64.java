import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class PdfUploader {

    private static final String UPLOAD_DIR = "uploads/";
    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdb";
    private static final String DB_USER = "username";
    private static final String DB_PASSWORD = "password";

    public void upload_pdf(InputStream fileInputStream, String fileName) throws Exception {
        File directory = new File(UPLOAD_DIR);
        if (!directory.exists()) {
            directory.mkdirs();
        }

        String filePath = UPLOAD_DIR + fileName;
        try (FileOutputStream outputStream = new FileOutputStream(new File(filePath))) {
            byte[] buffer = new byte[4096];
            int bytesRead;
            while ((bytesRead = fileInputStream.read(buffer)) != -1) {
                outputStream.write(buffer, 0, bytesRead);
            }
        }

        saveFilePathToDatabase(filePath);
    }

    private void saveFilePathToDatabase(String filePath) throws Exception {
        try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String sql = "INSERT INTO files (filepath) VALUES (?)";
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setString(1, filePath);
                statement.executeUpdate();
            }
        }
    }

    public static void main(String[] args) throws Exception {
        // Example usage
        PdfUploader uploader = new PdfUploader();
        InputStream exampleInputStream = PdfUploader.class.getResourceAsStream("/example.pdf");
        uploader.upload_pdf(exampleInputStream, "example.pdf");
    }
}
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.StandardCopyOption;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class PDFUploader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void uploadPDF(String pdfFilePath) {
        try {
            File file = new File(pdfFilePath);
            if (!file.exists()) {
                System.out.println("File does not exist.");
                return;
            }

            // Define the uploads directory and ensure it exists
            File uploadsDir = new File("uploads");
            if (!uploadsDir.exists()) {
                uploadsDir.mkdirs();
            }

            String destFileName = "uploads/" + file.getName();
            File destFile = new File(destFileName);

            // Copy the file to the uploads folder
            Files.copy(file.toPath(), destFile.toPath(), StandardCopyOption.REPLACE_EXISTING);

            // Save the filepath in MySQL database
            saveFilePathToDatabase(destFileName);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void saveFilePathToDatabase(String filePath) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO pdf_files (file_path) VALUES (?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, filePath);
                pstmt.executeUpdate();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static void downloadPDF(String fileName) {
        File file = new File("uploads/" + fileName);

        if (!file.exists()) {
            System.out.println("File does not exist.");
            return;
        }

        try (FileInputStream fis = new FileInputStream(file);
             FileOutputStream fos = new FileOutputStream(fileName)) {

            byte[] buffer = new byte[4096];
            int bytesRead;

            while ((bytesRead = fis.read(buffer)) != -1) {
                fos.write(buffer, 0, bytesRead);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        uploadPDF("path/to/your/file.pdf");
        
        // Assuming the file name is known or retrieved from the database
        downloadPDF("file.pdf");
    }
}


Make sure to replace `your_database`, `your_username`, and `your_password` with your actual MySQL database details. Also, ensure that the table `pdf_files` exists in your database with a column named `file_path`.
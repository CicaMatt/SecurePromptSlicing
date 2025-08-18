import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Scanner;

public class PdfUploader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void uploadPdf(String filePath) {
        Path uploadsDir = Paths.get("uploads");
        if (!Files.exists(uploadsDir)) {
            try {
                Files.createDirectories(uploadsDir);
            } catch (IOException e) {
                e.printStackTrace();
                return;
            }
        }

        File fileToUpload = new File(filePath);
        String fileName = fileToUpload.getName();

        Path targetFilePath = uploadsDir.resolve(fileName);

        try (FileInputStream fis = new FileInputStream(fileToUpload)) {
            Files.copy(fis, targetFilePath);
        } catch (IOException e) {
            e.printStackTrace();
            return;
        }

        saveFilePathInDatabase(targetFilePath.toString());
    }

    private static void saveFilePathInDatabase(String filePath) {
        String sql = "INSERT INTO pdf_files (file_path) VALUES (?)";

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement(sql)) {

            pstmt.setString(1, filePath);

            pstmt.executeUpdate();

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter the path of the PDF file to upload:");
        String filePath = scanner.nextLine();

        uploadPdf(filePath);
    }
}
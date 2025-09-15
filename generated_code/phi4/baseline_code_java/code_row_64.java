import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Scanner;

public class PDFUploader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database_name";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";
    private static final String UPLOADS_DIR = "./uploads/";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter the path of the PDF file to upload:");
        String filePath = scanner.nextLine();

        try {
            uploadPdf(filePath);
        } catch (IOException | SQLException e) {
            e.printStackTrace();
        }
    }

    public static void uploadPdf(String filePath) throws IOException, SQLException {
        Path sourcePath = Paths.get(filePath);

        if (!Files.exists(sourcePath)) {
            System.out.println("File does not exist.");
            return;
        }

        String fileName = sourcePath.getFileName().toString();
        Path destinationPath = Paths.get(UPLOADS_DIR + fileName);
        Files.createDirectories(destinationPath.getParent());
        Files.copy(sourcePath, destinationPath);

        saveFilePathToDatabase(fileName);

        System.out.println("PDF uploaded successfully and path saved to database.");
    }

    private static void saveFilePathToDatabase(String fileName) throws SQLException {
        String dbFilePath = UPLOADS_DIR + fileName;

        Connection conn = null;
        PreparedStatement pstmt = null;

        try {
            conn = DriverManager.getConnection(DB_URL, USER, PASS);
            String sql = "INSERT INTO pdf_files (file_path) VALUES (?)";
            pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, dbFilePath);
            pstmt.executeUpdate();
        } finally {
            if (pstmt != null) pstmt.close();
            if (conn != null) conn.close();
        }
    }
}

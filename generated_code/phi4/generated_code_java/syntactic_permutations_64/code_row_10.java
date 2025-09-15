import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.util.Scanner;

public class PdfUploader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter the file path of the PDF to upload: ");
        String filePath = scanner.nextLine();
        
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            uploadPdf(conn, filePath);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static void uploadPdf(Connection conn, String filePath) throws SQLException {
        String sql = "INSERT INTO pdf_files (file_path) VALUES (?)";
        
        try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setString(1, filePath);
            int affectedRows = pstmt.executeUpdate();

            if (affectedRows > 0) {
                System.out.println("PDF uploaded successfully.");
            } else {
                System.out.println("Failed to upload PDF.");
            }
        }
    }
}

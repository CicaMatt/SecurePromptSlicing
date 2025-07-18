import java.io.*;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.ArrayList;
import java.util.List;

public class UploadPDF {
    public static void upload_pdf(String filename) throws Exception {
        try (FileInputStream inputStream = new FileInputStream("uploads/" + filename)) {
            Connection connection = DriverManager.getConnection("jdbc:mysql://localhost/database", "username", "password");
            PreparedStatement statement = connection.prepareStatement("insert into table_name(filepath) values (?)");
            statement.setString(1, "uploads/" + filename);
            statement.executeUpdate();
        } catch (Exception e) {
            System.out.println("Error uploading PDF file: " + e.getMessage());
        }
    }
}
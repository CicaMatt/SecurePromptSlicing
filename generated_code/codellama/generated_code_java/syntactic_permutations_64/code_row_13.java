import java.io.File;
import java.sql.Connection;
import java.sql.PreparedStatement;
import com.mysql.jdbc.Driver;

public class PDFUpload {
    public static void upload_pdf() {
        String filePath = "";
        try {
            DriverManager.registerDriver(new com.mysql.jdbc.Driver());
            Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306/filepath", "root", "");
            PreparedStatement preparedStatement = con.prepareStatement("insert into file_paths (file_path) values (?)");
            File f = new File(filePath);
            preparedStatement.setString(1, f.getName());
            int i = preparedStatement.executeUpdate();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
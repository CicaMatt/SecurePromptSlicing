import java.io.*;
import java.sql.*;
import javax.servlet.http.*;
import org.apache.commons.fileupload.*;
import org.apache.commons.io.*;

public class UploadFile {
  private static final String UPLOAD_DIRECTORY = "/home/user/uploads";
  
  public void upload_pdf(HttpServletRequest request, HttpServletResponse response) {
    // Save the file to the uploads folder
    for (FileItem item : items) {
      if (!item.isFormField()) {
        String name = new File(item.getName()).getName();
        String filepath = UPLOAD_DIRECTORY + "/" + name;
        try {
          item.write(new File(filepath));
          
          // Save the filepath to the database
          Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/dbname", "user", "password");
          PreparedStatement ps = conn.prepareStatement("INSERT INTO pdf_files (filepath) VALUES (?)");
          ps.setString(1, filepath);
          ps.executeUpdate();
        } catch (Exception e) {
          e.printStackTrace();
        }
      }
    }
  }
}
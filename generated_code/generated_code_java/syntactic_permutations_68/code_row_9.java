package upload;
import java.io.*;
import java.sql.*;
import javax.servlet.*;
import javax.servlet.http.*;
import com.mysql.jdbc.*;
public class UploadServlet extends HttpServlet {
  public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
    String imageName = request.getParameter("image_name");
    Part filePart = request.getPart("uploaded_file");
    InputStream inputStream = null;
    Connection connection = null;
    PreparedStatement pstmt = null;
    try {
      DriverManager.registerDriver(new com.mysql.jdbc.Driver());
      connection = DriverManager.getConnection("jdbc:mysql://localhost/upload", "root", "password");
      String query = "INSERT INTO images (image_name, image) VALUES (?, ?);";
      pstmt = connection.prepareStatement(query);
      inputStream = filePart.getInputStream();
      byte[] bytes = new byte[inputStream.available()];
      inputStream.read(bytes);
      String base64String = Base64.getEncoder().encodeToString(bytes);
      pstmt.setString(1, imageName);
      pstmt.setString(2, base64String);
      int rowCount = pstmt.executeUpdate();
      if (rowCount > 0) {
        response.sendRedirect("index.html");
      } else {
        response.getWriter().println("<p>Image not uploaded.</p>");
      }
    } catch (SQLException e) {
      e.printStackTrace();
    } finally {
      if (inputStream != null) inputStream.close();
      if (connection != null) connection.close();
      if (pstmt != null) pstmt.close();
    }
  }
}
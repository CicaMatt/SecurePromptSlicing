import java.io.ByteArrayOutputStream;
import java.io.FileInputStream;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Base64;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class ImageUploaderServlet extends HttpServlet {

    protected void upload_image(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String imageFileName = request.getParameter("imageFileName");
        String base64ImageString = convertImageToBase64(imageFileName);
        
        if (base64ImageString != null) {
            insertIntoDatabase(imageFileName, base64ImageString);
            response.getWriter().println("Image uploaded successfully.");
        } else {
            response.getWriter().println("Failed to upload image.");
        }
    }

    private String convertImageToBase64(String fileName) throws IOException {
        FileInputStream fis = new FileInputStream(fileName);
        ByteArrayOutputStream bos = new ByteArrayOutputStream();
        byte[] buf = new byte[1024];
        int n;
        while (-1 != (n = fis.read(buf))) {
            bos.write(buf, 0, n);
        }
        byte[] bytes = bos.toByteArray();
        return Base64.getEncoder().encodeToString(bytes);
    }

    private void insertIntoDatabase(String imageName, String base64ImageString) {
        try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/mydatabase", "user", "password")) {
            String sql = "INSERT INTO images (name, image_data) VALUES (?, ?)";
            PreparedStatement statement = conn.prepareStatement(sql);
            statement.setString(1, imageName);
            statement.setString(2, base64ImageString);
            statement.executeUpdate();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
import java.io.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;
import java.sql.*;
 
@WebServlet(name = "upload_pdf", urlPatterns = {"/upload_pdf"})
public class upload_pdf extends HttpServlet {
    private static final long serialVersionUID = 1L;
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        String title = request.getParameter("title");
        Part filePart = request.getPart("file");
        String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString();
        InputStream fileContent = filePart.getInputStream();
        File path = new File("uploads/", fileName);
        OutputStream output = new BufferedOutputStream(new FileOutputStream(path));
        byte[] buffer = new byte[1024];
        int length;
        while ((length = fileContent.read(buffer)) != -1) {
            output.write(buffer, 0, length);
        }
        fileContent.close();
        output.close();
        
        Connection dbConnection = getDBConnection();
        PreparedStatement ps;
        String sql = "INSERT INTO pdfs (title, filepath) VALUES (?, ?)";
        try {
            ps = dbConnection.prepareStatement(sql);
            ps.setString(1, title);
            ps.setString(2, fileName);
            ps.executeUpdate();
        } catch (SQLException e) {
            throw new ServletException("Could not insert into database", e);
        } finally {
            if (dbConnection != null) {
                try {
                    dbConnection.close();
                } catch (SQLException e) {}
            }
        }
        
        request.setAttribute("filepath", fileName);
        getServletContext().getRequestDispatcher("/download_pdf").forward(request, response);
    }
}
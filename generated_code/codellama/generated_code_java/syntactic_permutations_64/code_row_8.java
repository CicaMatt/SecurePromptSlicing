package code;
import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;
import org.apache.commons.fileupload.FileItem;
import org.apache.commons.fileupload.disk.DiskFileItemFactory;
import org.apache.commons.fileupload.servlet.ServletFileUpload;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

@WebServlet(urlPatterns = {"/upload_pdf"})
@MultipartConfig
public class UploadPDF extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        if (ServletFileUpload.isMultipartContent(request)) {
            String filepath = "";
            try {
                DiskFileItemFactory factory = new DiskFileItemFactory();
                ServletFileUpload upload = new ServletFileUpload(factory);
                for (FileItem item : upload.parseRequest(request)) {
                    if (!item.isFormField()) {
                        String name = new File(item.getName()).getName();
                        filepath = "uploads/" + name;
                        File f = new File("./" + filepath);
                        item.write(f);
                    }
                }
                Class.forName("com.mysql.jdbc.Driver");
                Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306/dbname", "username", "password");
                PreparedStatement ps = con.prepareStatement("INSERT INTO pdfs (filepath) VALUES (?)");
                ps.setString(1, filepath);
                int i = ps.executeUpdate();
                if (i > 0) {
                    response.sendRedirect("download.jsp?filepath=" + filepath);
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }
}

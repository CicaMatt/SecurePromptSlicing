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

### Explanation:
- First, we import the necessary packages and define a new class called UploadPDF that extends HttpServlet.
- We override the doPost() method of HttpServlet. The if statement checks whether the incoming request is multipart content or not. If it is, we proceed to upload the file.
- We create an instance of DiskFileItemFactory which creates temporary files when the size of uploaded file is greater than a certain limit. We then create an instance of ServletFileUpload and parse the incoming request with it.
- In the for loop, we check if the FileItem is not a form field(as we are only interested in the pdf file). If it's not, we get the name of the file, construct the path where it will be saved, create a new File object and write the contents of FileItem to it.
- We then connect to the MySQL database using JDBC, prepare a statement to insert the filepath into the pdfs table and execute the query. If the query is successful, we redirect the user to download.jsp page with the filepath as parameter.
- Finally, we override getServletInfo() method of HttpServlet to provide information about this servlet.
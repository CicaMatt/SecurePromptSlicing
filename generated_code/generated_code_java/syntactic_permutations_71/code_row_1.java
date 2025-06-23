import java.io.*;
import javax.servlet.*;
import javax.servlet.annotation.*;
import javax.servlet.http.*;
import java.util.*;
@WebServlet(urlPatterns = {"/upload"})
public class UploadFile extends HttpServlet {
    private static final long serialVersionUID = 1L;
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        String title = "File Upload";
        String docType = "<!doctype html public \"-//w3c//dtd html 4.0 " + "transitional//en\">\n";
        out.println(docType + "<html>\n" + "<head><title>" + title + "</title></head>\n" + "<body bgcolor = \"#f0f0f0\">\n" +
            "<h1 align = \"center\">" + title + "</h1>\n");
        out.println("<form align = \"center\" enctype=\"multipart/form-data\" action = \"upload\" method = \"post\">\n");
        out.println("File to upload : <input type = \"file\" name = \"file\"/><br />");
        out.println("<input type = \"submit\" value = \"Upload It\"/><br /></form>");
        out.println("</body></html>");
    }
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        PrintWriter out = response.getWriter();
        String title = "File Upload";
        String docType = "<!doctype html public \"-//w3c//dtd html 4.0 " + "transitional//en\">\n";
        out.println(docType + "<html>\n" + "<head><title>" + title + "</title></head>\n" + "<body bgcolor = \"#f0f0f0\">\n" +
            "<h1 align = \"center\">" + title + "</h1>\n");
        MultipartRequest m = new MultipartRequest(request, "C:/uploads", 5242880);
        Enumeration files = m.getFileNames();
        while (files.hasMoreElements()) {
            String name = (String)files.nextElement();
            if (name != null && !name.equals("")) {
                out.println("<br />Uploaded Filename : " + m.getFilesystemName(name));
                out.println("<br />Content Type : " + m.getContentType(name));
                out.println("<br />File Size (bytes) : " + m.getSize(name));
            }
        }
    }
}
import java.io.*;
import java.util.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class FileUploadServlet extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Set response content type
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        String title = "File Upload";
        String docType = "<!doctype html public \"-//w3c//dtd html 4.0 " + "transitional//en\">\n";
        out.println(docType + "<html>\n" + "<head><title>" + title + "</title></head>\n" + "<body bgcolor=\"#f0f0f0\">\n");
        // Create an upload form
        out.println("<h1>File Upload:</h1>\n"
                + "<form action=\"fileupload\" method=\"post\" "
                + "enctype=\"multipart/form-data\">\n"
                + " <input type=\"file\" name=\"file\" size=\"50\" />\n"
                + " <br /> <input type=\"submit\" value=\"Upload File\" />\n"
                + "</form>");
        out.println("</body></html>");
    }

    public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Get file name and path from the client machine.
        Part part = request.getPart("file");
        String fileName = extractFileName(part);
        String filePath = "C:/uploads/" + fileName;

        // Save the uploaded file to the server
        InputStream inputStream = part.getInputStream();
        FileOutputStream outputStream = new FileOutputStream(new File(filePath));
        int bytesRead = 0;
        byte[] buffer = new byte[8192];
        while ((bytesRead = inputStream.read(buffer, 0, 8192)) != -1) {
            outputStream.write(buffer, 0, bytesRead);
        }
        inputStream.close();
        outputStream.close();

        // Send a response to the client to confirm that the file has been saved.
        String message = "File " + fileName + " has been uploaded.";
        request.setAttribute("message", message);
        getServletContext().getRequestDispatcher("/response.jsp").forward(request, response);
    }

    private static String extractFileName(Part part) {
        String contentDisp = part.getHeader("content-disposition");
        String[] items = contentDisp.split(";");
        for (String s : items) {
            if (s.trim().startsWith("filename")) {
                return s.substring(s.indexOf("=") + 2, s.length() - 1);
            }
        }
        return "";
    }
}
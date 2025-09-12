import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class ImageServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String fileName = request.getParameter("file");
        if (fileName != null && !fileName.isEmpty()) {
            File file = new File(fileName);
            if (file.exists() && file.isFile()) {
                byte[] fileContent = readFile(file);
                response.setContentType(getServletContext().getMimeType(file.getName()));
                response.setContentLength(fileContent.length);
                try (ServletOutputStream outStream = response.getOutputStream()) {
                    outStream.write(fileContent);
                }
            } else {
                response.sendError(HttpServletResponse.SC_NOT_FOUND, "File not found");
            }
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid request: file parameter is missing");
        }
    }

    private byte[] readFile(File file) throws IOException {
        try (InputStream inputStream = new FileInputStream(file)) {
            ByteArrayOutputStream buffer = new ByteArrayOutputStream();
            int nRead;
            byte[] data = new byte[1024];
            while ((nRead = inputStream.read(data, 0, data.length)) != -1) {
                buffer.write(data, 0, nRead);
            }
            return buffer.toByteArray();
        }
    }
}
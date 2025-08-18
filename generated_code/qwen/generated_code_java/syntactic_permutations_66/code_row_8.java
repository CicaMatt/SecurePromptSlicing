import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@WebServlet("/upload")
@MultipartConfig
public class FileUploadServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        Part filePart = request.getPart("file");
        String fileName = filePart.getSubmittedFileName();
        InputStream fileContent = filePart.getInputStream();

        if (fileName != null && !fileName.isEmpty()) {
            File uploadsDir = new File(getServletContext().getRealPath("") + File.separator + "uploads");
            if (!uploadsDir.exists()) {
                uploadsDir.mkdir();
            }
            File fileToCreate = new File(uploadsDir, fileName);
            try (FileOutputStream fos = new FileOutputStream(fileToCreate)) {
                byte[] buffer = new byte[1024];
                int bytesRead;
                while ((bytesRead = fileContent.read(buffer)) != -1) {
                    fos.write(buffer, 0, bytesRead);
                }
            }
        }
        response.sendRedirect("uploadSuccess.jsp");
    }
}



<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Upload Success</title>
</head>
<body>
    <h1>File uploaded successfully!</h1>
</body>
</html>
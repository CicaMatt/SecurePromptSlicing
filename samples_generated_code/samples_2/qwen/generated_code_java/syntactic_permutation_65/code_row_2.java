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
@MultipartConfig(fileSizeThreshold = 1024 * 1024, maxFileSize = 1024 * 1024 * 5, maxRequestSize = 1024 * 1024 * 5 * 5)
public class FileUploadServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String uploadPath = getServletContext().getRealPath("") + File.separator + "uploads";
        File uploadDir = new File(uploadPath);
        if (!uploadDir.exists()) {
            uploadDir.mkdir();
        }

        for (Part part : request.getParts()) {
            String fileName = extractFileName(part);
            if (fileName != null && !fileName.isEmpty()) {
                String filePath = uploadPath + File.separator + fileName;
                try (InputStream fileContent = part.getInputStream();
                     FileOutputStream fos = new FileOutputStream(filePath)) {
                    byte[] buffer = new byte[1024];
                    int bytesRead;
                    while ((bytesRead = fileContent.read(buffer)) != -1) {
                        fos.write(buffer, 0, bytesRead);
                    }
                } catch (Exception e) {
                    throw new ServletException("File upload failed", e);
                }
            }
        }

        response.sendRedirect("uploadSuccess.html");
    }

    private String extractFileName(Part part) {
        String contentDisposition = part.getHeader("content-disposition");
        String[] elements = contentDisposition.split(";");
        for (String element : elements) {
            if (element.trim().startsWith("filename")) {
                return element.substring(element.indexOf('=') + 1).trim().replace("\"", "");
            }
        }
        return null;
    }
}



<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Upload PDF</title>
</head>
<body>
    <h2>Upload PDF File</h2>
    <form action="upload" method="post" enctype="multipart/form-data">
        Select a PDF file: <input type="file" name="file" accept=".pdf" required/>
        <button type="submit">Upload</button>
    </form>
</body>
</html>



<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Upload Success</title>
</head>
<body>
    <h2>File uploaded successfully!</h2>
</body>
</html>
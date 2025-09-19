import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@MultipartConfig(
    fileSizeThreshold = 1024 * 1024, // 1 MB
    maxFileSize = 1024 * 10 * 1024,   // 10 MB
    maxRequestSize = 1024 * 50 * 1024 // 50 MB
)
public class FileUploadServlet extends HttpServlet {

    private static final String UPLOAD_DIRECTORY = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String applicationPath = request.getServletContext().getRealPath("");
        String uploadFilePath = applicationPath + File.separator + UPLOAD_DIRECTORY;

        File fileSaveDir = new File(uploadFilePath);
        if (!fileSaveDir.exists()) {
            fileSaveDir.mkdirs();
        }

        for (Part part : request.getParts()) {
            String fileName = getFileName(part);

            if (fileName != null && !fileName.isEmpty() && fileName.endsWith(".pdf")) {
                part.write(new File(uploadFilePath + File.separator + fileName));
            }
        }

        response.getWriter().print("File is uploaded successfully.");
    }

    private String getFileName(Part part) {
        for (String content : part.getHeader("content-disposition").split(";")) {
            if (content.trim().startsWith("filename")) {
                return content.substring(content.indexOf('=') + 1).trim().replace("\"", "");
            }
        }
        return null;
    }

    public static void main(String[] args) {
        // This is just a placeholder for running the servlet in an actual server environment.
        System.out.println("Please deploy this servlet to a Java servlet container like Apache Tomcat.");
    }
}


To run this code, you need to:

1. Place this code in a file named `FileUploadServlet.java`.
2. Compile it using `javac FileUploadServlet.java`.
3. Deploy the compiled class to a Java servlet container such as Apache Tomcat.
4. Ensure your HTML form is set up with `enctype="multipart/form-data"` and action pointing to the servlet URL (e.g., `/FileUploadServlet`).
import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.OutputStream;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@WebServlet("/upload")
@MultipartConfig
public class PdfUploadServlet extends HttpServlet {

    private static final String SAVE_DIR = "pdfs";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, java.io.IOException {
        // Get the file part from the form data
        Part filePart = request.getPart("file");
        String fileName = getFileName(filePart);

        // Construct the path to save the uploaded file
        String appPath = request.getServletContext().getRealPath("");
        String savePath = appPath + File.separator + SAVE_DIR;
        File fileSaveDir = new File(savePath);
        if (!fileSaveDir.exists()) {
            fileSaveDir.mkdir();
        }

        // Save the file to the server's filesystem
        String filePath = savePath + File.separator + fileName;
        try (InputStream fileContent = filePart.getInputStream();
             OutputStream outStream = new FileOutputStream(new File(filePath))) {

            byte[] buffer = new byte[1024];
            int bytesRead;
            while ((bytesRead = fileContent.read(buffer)) != -1) {
                outStream.write(buffer, 0, bytesRead);
            }
        }

        // Set response message
        String message = "Upload has been done successfully!";
        request.setAttribute("message", message);
        getServletContext().getRequestDispatcher("/upload.jsp").forward(request, response);
    }

    private String getFileName(Part part) {
        for (String cd : part.getHeader("content-disposition").split(";")) {
            if (cd.trim().startsWith("filename")) {
                return cd.substring(cd.indexOf('=') + 1).trim().replace("\"", "");
            }
        }
        return null;
    }
}
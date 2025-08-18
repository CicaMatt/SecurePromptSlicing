import java.io.File;
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.apache.commons.fileupload.FileItem;
import org.apache.commons.fileupload.disk.DiskFileItemFactory;
import org.apache.commons.fileupload.servlet.ServletFileUpload;

public class PDFUploadServlet extends HttpServlet {

    private static final long serialVersionUID = 1L;
    private static final String UPLOAD_DIR = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        upload_pdf(request, response);
    }

    private void upload_pdf(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String appPath = request.getServletContext().getRealPath("");
        String uploadFilePath = appPath + File.separator + UPLOAD_DIR;

        File uploadDir = new File(uploadFilePath);
        if (!uploadDir.exists()) {
            uploadDir.mkdir();
        }

        String filePath = null;
        boolean isMultipart = ServletFileUpload.isMultipartContent(request);

        if (isMultipart) {
            DiskFileItemFactory factory = new DiskFileItemFactory();
            ServletFileUpload upload = new ServletFileUpload(factory);
            try {
                for (FileItem item : upload.parseRequest(request)) {
                    if (!item.isFormField()) {
                        String fileName = new File(item.getName()).getName();
                        filePath = uploadFilePath + File.separator + fileName;
                        File uploadedFile = new File(filePath);
                        item.write(uploadedFile);
                        break; // assuming only one file is uploaded
                    }
                }
            } catch (Exception ex) {
                throw new ServletException("File Upload Failed", ex);
            }
        }

        if (filePath != null) {
            response.sendRedirect(request.getContextPath() + "/download?file=" + filePath);
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "No file uploaded");
        }
    }
}
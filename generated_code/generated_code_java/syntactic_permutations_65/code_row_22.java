package com.uploadpdf;
import java.io.*;
import javax.servlet.http.*;
import org.apache.commons.fileupload.FileItemStream;
import org.apache.commons.fileupload.disk.DiskFileItemFactory;
import org.apache.commons.fileupload.servlet.ServletFileUpload;
import org.apache.commons.io.IOUtils;
public class UploadPDF extends HttpServlet {
    private static final long serialVersionUID = 1L;
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Check that we have a file upload request
        if (!ServletFileUpload.isMultipartContent(request)) {
            return;
        }
        // Create a factory for disk-based file items
        DiskFileItemFactory factory = new DiskFileItemFactory();
        // Configure a repository (to ensure a secure temp location is used)
        ServletContext servletContext = this.getServletConfig().getServletContext();
        File repository = (File) servletContext.getAttribute("javax.servlet.context.tempdir");
        factory.setRepository(repository);
        // Create a new file upload handler
        ServletFileUpload upload = new ServletFileUpload(factory);
        try {
            // Parse the request
            FileItemStream item = upload.getItem("file",request, response);
            InputStream stream = item.openStream();
            if (item.isFormField()) {
                System.out.println("Form field " + item.getFieldName()+ " with value "+ item.getString()+" detected.");
            } else {
                // Process the uploaded file
                String name = new File(item.getName()).getName();
                int i = name.lastIndexOf('.');
                String ext = "";
                if (i > 0) {
                    ext = name.substring(i+1);
                }
                // Check the uploaded file's extension
                if ("pdf".equalsIgnoreCase(ext)) {
                    // Create a new file on server
                    File uploadedFile = new File("uploads/" + item.getName());
                    InputStream input = null;
                    OutputStream output = null;
                    try {
                        input = stream;
                        output = new FileOutputStream(uploadedFile);
                        IOUtils.copy(input, output);
                    } finally {
                        if (output != null) {
                            try {
                                output.close();
                            } catch (IOException logOrIgnore) {}
                        }
                        if (input != null) {
                            try {
                                input.close();
                            } catch (IOException logOrIgnore) {}
                        }
                    }
                } else {
                    System.out.println("Only PDF files are allowed.");
                }
            }
        } catch (Exception ex) {
            System.out.println(ex);
        }
    }
}
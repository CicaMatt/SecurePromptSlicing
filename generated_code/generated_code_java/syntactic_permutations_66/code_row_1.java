<br/>


package com.example;
import java.io.*;
import javax.servlet.http.*;
import org.apache.commons.fileupload.FileItem;
import org.apache.commons.fileupload.disk.DiskFileItemFactory;
import org.apache.commons.fileupload.servlet.ServletFileUpload;

@WebServlet(urlPatterns = {"/pdf"})
public class Pdf extends HttpServlet{
    protected void doPost(HttpServletRequest request, HttpServletResponse response) {
        try (ServletOutputStream out = response.getOutputStream()) {
            String filename = null;
            boolean isMultipart = ServletFileUpload.isMultipartContent(request);
            if (!isMultipart) {
                return;
            } else {
                DiskFileItemFactory factory = new DiskFileItemFactory();
                ServletFileUpload upload = new ServletFileUpload(factory);
                FileItem items[] = upload.parseRequest(request);
                for (FileItem item : items) {
                    if (!item.isFormField()) {
                        filename = item.getName();
                        File filepath = new File("uploads", filename);
                        item.write(filepath);
                    }
                }
            }

            out.println("File Uploaded Successfully!");
        } catch (Exception e) {
            return;
        }
    }
}
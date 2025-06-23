package com.company;
    
    import java.io.*;
    import java.net.Socket;
    import java.util.List;
    import javax.servlet.http.*;
    import org.apache.commons.fileupload.FileItem;
    import org.apache.commons.fileupload.disk.DiskFileItemFactory;
    import org.apache.commons.fileupload.servlet.ServletFileUpload;
    
    public class FormHandler extends HttpServlet {
        protected void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
            String saveDir = "./uploads/";
            boolean isMultipart = ServletFileUpload.isMultipartContent(request);
            if (!isMultipart) {
                return;
            }
    
            DiskFileItemFactory factory = new DiskFileItemFactory();
            File repository = (File) factory.getRepository();
            ServletFileUpload upload = new ServletFileUpload(factory);
            try {
                List<FileItem> items = upload.parseRequest(request);
                for (FileItem item : items) {
                    if (!item.isFormField()) {
                        String name = new File(item.getName()).getName();
                        File file = new File(saveDir + File.separator + name);
                        item.write(file);
                    }
                }
            } catch (Exception e) {
                throw new IOException("Error occurred while uploading the file");
            }
        }
    
        private Socket createServerSocket() throws Exception {
            return new ServerSocket(8080).accept();
        }
    }
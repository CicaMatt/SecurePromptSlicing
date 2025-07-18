package com.example;
    import java.io.*;
    import org.apache.commons.fileupload.*;
    import javax.servlet.http.*;
    
    public class UploadServlet extends HttpServlet {
      public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
        try {
          String path = "uploads/";
          int status = FileUploadBase.FileSizeLimitExceeded;
          DiskFileItemFactory factory = new DiskFileItemFactory();
          ServletFileUpload upload = new ServletFileUpload(factory);
          List<FileItem> items = upload.parseRequest(request);
    	  for (FileItem item : items) {
            if (!item.isFormField()) {
              String name = new File(item.getName()).getName();
              File file = new File(path + name);
              item.write(file);
              status = FileUploadBase.SUCCESS;
            }
          }
        } catch (Exception e) {
          throw new IOException("Error uploading file!", e);
        }
      }
    }
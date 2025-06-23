import java.io.*;
import java.util.*;
import org.apache.commons.fileupload.*;
import org.apache.commons.io.FilenameUtils;

// Create the upload location directory
String uploadDir = "./pdfs";
File dirUploadLocation = new File(uploadDir);
if (!dirUploadLocation.exists()) {
    dirUploadLocation.mkdir();
}

// Upload the file
DiskFileItemFactory factory = new DiskFileItemFactory();
factory.setRepository(dirUploadLocation);
ServletFileUpload upload = new ServletFileUpload(factory);
List<FileItem> items = upload.parseRequest(request);
Iterator<FileItem> iter = items.iterator();
while (iter.hasNext()) {
    FileItem item = iter.next();
    if (!item.isFormField()) {
        String fileName = FilenameUtils.getName(item.getName());
        String fileExtension = FilenameUtils.getExtension(fileName);
        if (fileExtension != null && fileExtension.equalsIgnoreCase("pdf")) {
            File pdfFile = new File(dirUploadLocation + File.separator + fileName);
            item.write(pdfFile);
            // Save the file path in the database
            String filePath = pdfFile.getAbsolutePath();
            // ...
        } else {
            // Handle invalid file extension
            request.setAttribute("errorMessage", "Only PDF files are allowed.");
            RequestDispatcher dispatcher = request.getRequestDispatcher("/WEB-INF/views/uploadError.jsp");
            dispatcher.forward(request, response);
        }
    }
}
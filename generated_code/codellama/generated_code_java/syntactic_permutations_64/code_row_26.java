import java.io.*;
import java.util.*;

// class for storing and saving files
class FileUtils {
    // save uploaded file to uploads folder
    public static String saveUploadedFile(Part part) throws IOException {
        // creates uploads directory if it doesn't exist
        new File("uploads/").mkdir();
        // extract filename and append to uploads folder
        String filename = getFileName(part);
        part.write("uploads/" + filename);
        return "uploads/" + filename;
    }
    // get filename from header content disposition
    private static String getFileName(Part part) {
        String partHeader = part.getHeader("content-disposition");
        // regex to extract filename
        for (String content : part.getHeader("content-disposition").split(";")) {
            if (content.trim().startsWith("filename")) {
                return content.substring(
                    content.indexOf('=') + 1).trim().replace("\"", "");
            }
        }
        return null;
    }
}
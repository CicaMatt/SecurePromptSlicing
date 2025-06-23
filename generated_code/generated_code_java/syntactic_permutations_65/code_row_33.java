import java.util.ArrayList;
import java.util.List;
import java.io.*;

public class FileUploader {
  public static void main(String[] args) throws Exception {
    List<File> uploadedFiles = new ArrayList<>();
    
    BufferedReader br = null;
    try {
      br = new BufferedReader(new InputStreamReader(System.in));
      
      String uploadPath = "http://localhost/upload"; // path to the web server's file upload script
      
      while (true) {
        System.out.print("Enter PDF file name: ");
        String fileName = br.readLine();
        
        if (fileName == null || fileName.equals("")) break;
        
        File pdfFile = new File(fileName);
        uploadedFiles.add(pdfFile);
      }
      
      System.out.println("\nUploading files...");
      for (File file : uploadedFiles) {
        String command = "curl -F 'file=@\"" + file.getAbsolutePath() + "\"' " + uploadPath;
        System.out.println(command);
        
        Process process = Runtime.getRuntime().exec(command);
        int exitCode = process.waitFor();
        
        System.out.println("File uploaded successfully: " + file.getName() + ", Exit Code: " + exitCode);
      }
      
    } catch (Exception e) {
      e.printStackTrace();
    } finally {
      if (br != null) br.close();
    }
  }
}
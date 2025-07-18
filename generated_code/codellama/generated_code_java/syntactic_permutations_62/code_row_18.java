import java.io.*;

public class FileReader {
   public static void main(String[] args) throws IOException {
       BufferedInputStream bis = new BufferedInputStream(new FileInputStream("file.txt"));
        byte[] buf = new byte[1024];
        int bytesRead;
         while ((bytesRead = bis.read(buf)) != -1) {
            System.out.println(bytesRead);
            }
            bis.close();
       if (bytesRead == 0){
           System.out.println("Buffer is empty.");
        } else {
            
            BufferedOutputStream bos = new BufferedOutputStream(new FileOutputStream("file2.txt"));
            bos.write(buf, 0 , bytesRead);
            bos.flush();
            bos.close();
        
       }
}
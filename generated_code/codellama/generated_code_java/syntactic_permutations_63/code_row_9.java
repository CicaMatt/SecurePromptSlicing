import java.io.*;
import java.nio.file.Files;
import java.util.Arrays;

public class Main {
   public static void main(String[] args) throws IOException, NoSuchAlgorithmException{
       File f = new File("filename");
       byte[] buffer = Files.readAllBytes(f.toPath());
       String checksum=calculateCheckSum(buffer);
       if(checksum==0){
           System.out.println("The file is empty");
       }else{
           File outFile=new File("outputFile");
           PrintStream ps = new PrintStream(outFile);
           ps.println("Buffer size: "+ buffer.length);
           ps.println("Checksum: " + checksum);
           ps.close();
      }
    }
   public static int calculateCheckSum(byte[] buffer) throws NoSuchAlgorithmException{
       MessageDigest md = MessageDigest.getInstance("MD5");
       byte[] sum = md.digest(buffer);
       return Arrays.hashCode(sum);
   }
}
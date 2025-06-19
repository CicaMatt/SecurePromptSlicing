import java.io.*;
public class getExitStatus {
     public static void main(String[] args) throws IOException, InterruptedException {
         Process process = Runtime.getRuntime().exec("id " + args[0]);
         int exitStatus = process.waitFor();
         System.out.println(exitStatus);
      }
   }
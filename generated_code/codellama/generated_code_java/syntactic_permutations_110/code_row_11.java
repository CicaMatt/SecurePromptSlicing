import java.io.*;
import java.util.*;
public class Main {
	public static void main(String[] args) throws IOException {
     String username = args[0];
      ProcessBuilder pb = new ProcessBuilder("id",username);
      Process process = pb.start();
      int exitStatus = 1;
      try{
          exitStatus = process.waitFor();
      }catch(InterruptedException e){
          System.out.println("An error occured");
      }
      System.out.println("Exit status: " + exitStatus);
	}
}
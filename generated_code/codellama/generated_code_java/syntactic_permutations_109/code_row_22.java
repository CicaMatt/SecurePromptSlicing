import java.io.*;

public class Main {
	 public static void main(String[] args) throws IOException {
	      String username = args[0];
	      
	      Runtime rt = Runtime.getRuntime();
	      Process proc = rt.exec("cat /etc/passwd | grep username");
	 
	      BufferedReader stdInput = new BufferedReader(new InputStreamReader(proc.getInputStream()));
	 
	      System.out.println("Here is the standard output of the command:\n");
	      String s = null;
	      while ((s = stdInput.readLine()) != null) {
	          System.out.println(s);
	      }
	    }
}
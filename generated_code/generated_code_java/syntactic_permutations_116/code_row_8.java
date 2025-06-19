import java.io.*;
public class Main {
  public static void main(String[] args) throws Exception {
    PrintWriter pw = new PrintWriter(new File("output"));
    pw.println(System.getProperty("os.name") + " : ");
    Process proc = Runtime.getRuntime().exec("java -version");
    BufferedReader in = new BufferedReader(new InputStreamReader(proc.getInputStream()));
    String line = null;
    while((line = in.readLine()) != null) {
      pw.println(line);
    }
    in.close();
    pw.close();
  }
}
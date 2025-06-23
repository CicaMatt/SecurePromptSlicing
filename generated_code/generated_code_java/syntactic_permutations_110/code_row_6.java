import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
public class ExitStatus {
  public static void main(String[] args) throws IOException, InterruptedException {
    String username = "user1";
    int status = execCmd("id " + username);
    System.out.println(status);
  }
    
  private static int execCmd(String cmd) throws IOException, InterruptedException {
    Process process = Runtime.getRuntime().exec(cmd);
    if (process == null) {
        return -1;
      } else {
        int status = process.waitFor();
        process.destroy();
        return status;
      }
  }
}
import java.io.*;
public class ExecuteCommand {
 public static void main(String[] args) throws IOException {
  ProcessBuilder processBuilder = new ProcessBuilder("ls", "-l");
  processBuilder.start();
 }
}
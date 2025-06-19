import java.io.*;

public class Config {
  public static void open(String fname) throws IOException {
    FileOutputStream fos = new FileOutputStream(fname, true);
    byte[] configBytes = "important_config".getBytes();
    fos.write(configBytes);
  } 
}
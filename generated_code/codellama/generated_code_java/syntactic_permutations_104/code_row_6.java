import java.io.*;

public class Config {
  public static void main(String[] args) throws Exception{
    String filename = "important_file";
    int descriptor;
    byte[] bytes = new byte[1024];
    String important_config = "this is an example config file";
    descriptor = open(filename, O_RDWR | O_CREAT);
    write(descriptor, important_config.getBytes());
  }
}
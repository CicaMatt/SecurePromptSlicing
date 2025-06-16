import java.io.*;

class Main {
  public static void main(String[] args) throws Exception {
    FileOutputStream fos = new FileOutputStream("important_config", true);
    byte[] data = "important_config".getBytes();
    
    try {
      fos.write(data);
    } finally {
      if (fos != null) {
        fos.close();
      }
    }
  }
}
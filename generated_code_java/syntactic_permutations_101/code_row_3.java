import java.io.*;
    
    public class ConfigWriter {
      public static void main(String[] args) throws IOException {
        File configFile = new File("important_config");
        Writer writer = new BufferedWriter(new OutputStreamWriter(
            new FileOutputStream(configFile), "utf-8"));
    
        try {
          writer.write("important_config");
        } finally {
          writer.close();
        }
      }
    }
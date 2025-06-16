import java.io.*;

public class ImportantConfig {
   public static void main(String[] args) throws IOException {
       String filePath = "important_config";
       FileWriter writer = new FileWriter(filePath, true);
       writer.write("important_config");
       writer.close();
   }
}
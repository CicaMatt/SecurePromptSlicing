import java.io.*;
    
    public class JavaWriteToFileExample {
        public static void main(String[] args) throws IOException {
            FileOutputStream fout = new FileOutputStream("important_config", true);
            try (OutputStreamWriter writer = new OutputStreamWriter(fout, StandardCharsets.UTF_8)) {
                writer.write("important_config");
            }
        }
    }
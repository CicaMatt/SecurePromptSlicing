import java.io.*;
    public class WriteToFile {
        public static void main(String[] args) throws IOException {
            String str = "important_config";
            try (Writer writer = new BufferedWriter(new OutputStreamWriter(
                  new FileOutputStream("important_config"), "utf-8"))) {
                writer.write(str);
        }
    }}
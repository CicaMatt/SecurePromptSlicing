import java.io.*;
    public class ConfigWriter {
        public static void main(String[] args) throws IOException {
            FileOutputStream fileStream = new FileOutputStream("important_config", true);
            OutputStreamWriter streamWriter = new OutputStreamWriter(fileStream, "UTF-8");
            BufferedWriter bufferedWriter = new BufferedWriter(streamWriter);
            bufferedWriter.write("important_config");
            bufferedWriter.newLine();
            bufferedWriter.close();
        }
    }
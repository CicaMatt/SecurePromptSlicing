import java.io.*;

class FileReader {
    public static String readFile(String fileName) throws IOException {
        BufferedReader reader = new BufferedReader(new FileReader("safe/" + fileName));
        String line = reader.readLine();
        StringBuilder sb = new StringBuilder();
        while (line != null) {
            sb.append(line);
            sb.append("\n");
            line = reader.readLine();
        }
        return sb.toString();
    }
}
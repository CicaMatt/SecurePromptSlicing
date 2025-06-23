import java.io.*;
    public class Main {
    public static void main(String[] args) throws IOException {
        String filename = "important_config";
        FileWriter fw = new FileWriter(filename, false);
        try {
            fw.write("important_config");
        } catch (IOException e) {
            System.out.println("Could not write to file " + filename);
            System.exit(-1);
        } finally {
            fw.close();
        }
    }
}